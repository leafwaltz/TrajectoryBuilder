//messenger.h
#ifndef MESSENGER_H
#define MESSENGER_H

#include "userheaders.h"

typedef struct _Message
{
    int     type;
    void*   message;
}Message;

using TaskMessages = vector<Message>;

class Messenger:public QObject
{
    Q_OBJECT

public:

    static Messenger*           GetInstance();

    void                        PostMessage(Message msg);

    void                        PostMessageWithoutInforming(Message msg);

    Message                     ReceiveMessage(int type);

    void                        Initialize();

    void                        Destroy();

private:

    Messenger();

    map<int,pthread_mutex_t>    m_messageTempMutex;

    map<int,queue<Message>>     m_messageTemp;

    static Messenger*           m_pInstance;

    // ~TaskManager(){};
signals:

    void                        sig_newMessageIn(int type);
};

#endif // MESSENGER_H
