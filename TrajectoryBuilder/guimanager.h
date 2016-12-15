#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "userheaders.h"
#include "task.h"
#include "messenger.h"

namespace Ui {
class GuiManager;
}

class GuiManager : public QWidget
{
    Q_OBJECT

public:
    explicit GuiManager(QWidget *parent = 0);
    ~GuiManager();

public slots:
    void on_textBrowser_destroyed();
    void update(int messagetype);

private:
    Ui::GuiManager *ui;

    QPainter m_painter;
    QImage   m_image;

signals:

    void sig_pushButton_down();
private slots:
    void on_addCmdButton_clicked();
};

#endif // GUIMANAGER_H
