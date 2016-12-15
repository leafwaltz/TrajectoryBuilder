#include "guimanager.h"
#include "ui_guimanager.h"

GuiManager::GuiManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuiManager)
{
    ui->setupUi(this);

    ui->positionxLineEdit->setText("0");
    ui->positionyLineEdit->setText("0");
    ui->velocityLineEdit->setText("0");
    ui->accelerationLineEdit->setText("0");
    ui->decelerationLineEdit->setText("0");
    ui->jerkLineEdit->setText("0");

    m_image = QImage(500,500,QImage::Format_ARGB32);

    connect(Messenger::GetInstance(),
            SIGNAL(sig_newMessageIn(int)),
            this,
            SLOT(update(int)));
}

GuiManager::~GuiManager()
{
    delete ui;
}

void GuiManager::update(int messagetype)
{
    Message msg=Messenger::GetInstance()->ReceiveMessage(messagetype);
    Point2F currentPosition={0,0};
    Point2F lastPosition={0,0};

    switch (msg.type)
    {
    case type_task_trajectory_generator:

        currentPosition = ((tAxisSetpoint)msg.message)->Position;

        m_painter.begin(&m_image);

        m_painter.drawLine(QPoint(lastPosition.x,lastPosition.y),QPoint(currentPosition.x,currentPosition.y));

        m_painter.end();

        lastPosition = currentPosition;

        ui->canvas->setPixmap(QPixmap::fromImage(m_image));

        ui->currentVelocityLineEdit->setText(QString::number(((tAxisSetpoint)msg.message)->Velocity));

    default:
        Messenger::GetInstance()->PostMessageWithoutInforming(msg);
        break;
    }
}

void GuiManager::on_textBrowser_destroyed()
{
}

void GuiManager::on_addCmdButton_clicked()
{
    tPosCmd cmd = new _tPosCmd_;

    cmd->Position.x     =   ui->positionxLineEdit->text().toFloat();
    cmd->Position.y     =   ui->positionyLineEdit->text().toFloat();
    cmd->Velocity       =   ui->velocityLineEdit->text().toFloat();
    cmd->Acceleration   =   ui->accelerationLineEdit->text().toFloat();
    cmd->Deceleration   =   ui->decelerationLineEdit->text().toFloat();
    cmd->Jerk           =   ui->jerkLineEdit->text().toFloat();
    cmd->Request        =   true;
    cmd->Response       =   false;
    cmd->Done           =   false;

    Message msg;

    msg.type = type_set_task_command;
    msg.message = cmd;

    Messenger::GetInstance()->PostMessageWithoutInforming(msg);

    ui->textBrowser->append("New Command Added:");
    ui->textBrowser->append("Positionx:" + QString::number(cmd->Position.x));
    ui->textBrowser->append("Positiony:" + QString::number(cmd->Position.y));
    ui->textBrowser->append("Velocity:" + QString::number(cmd->Velocity));
    ui->textBrowser->append("Acceleration:" + QString::number(cmd->Acceleration));
    ui->textBrowser->append("Deceleration:" + QString::number(cmd->Deceleration));
    ui->textBrowser->append("Jerk:" + QString::number(cmd->Jerk));
}
