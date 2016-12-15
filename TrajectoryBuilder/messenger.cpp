#include "messenger.h"

Messenger* Messenger::m_pInstance = nullptr;

Messenger::Messenger()
{
}

void Messenger::PostMessage(Message msg)
{
    PostMessageWithoutInforming(msg);

    emit sig_newMessageIn(msg.type);
}

void Messenger::PostMessageWithoutInforming(Message msg)
{
    map<int,queue<Message>>::iterator it = m_messageTemp.find(msg.type);

    if(it==m_messageTemp.end())
    {
        queue<Message> newMessageQueue;
        newMessageQueue.push(msg);
        pthread_mutex_t newMutex;
        pthread_mutex_init(&newMutex,NULL);
        m_messageTemp.insert(pair<int,queue<Message>>{msg.type,newMessageQueue});
        m_messageTempMutex.insert(pair<int,pthread_mutex_t>{msg.type,newMutex});
    }
    else
    {
        pthread_mutex_lock(&m_messageTempMutex[msg.type]);
        it->second.push(msg);
        pthread_mutex_unlock(&m_messageTempMutex[msg.type]);
    }
}

Message Messenger::ReceiveMessage(int type)
{
    Message msg{0,nullptr};
    map<int,queue<Message>>::iterator it = m_messageTemp.find(type);
    if(!(it==m_messageTemp.end()))
    {
        if(!(it->second.empty()))
        {
            pthread_mutex_lock(&m_messageTempMutex[type]);
            msg=it->second.front();
            it->second.pop();
            pthread_mutex_unlock(&m_messageTempMutex[type]);
        }
    }
    return msg;
}

void Messenger::Initialize()
{

}

void Messenger::Destroy()
{
    delete m_pInstance;
}

Messenger* Messenger::GetInstance()
{
    if(m_pInstance==nullptr)
    {
        m_pInstance = new Messenger();
    }
    return m_pInstance;
}
