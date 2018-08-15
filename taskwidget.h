#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QtWidgets>
#include "task.h"

class TaskWidget:public QGroupBox
{
    Q_OBJECT
public:
    TaskWidget(const QString& title ,QWidget *parent=NULL);
    virtual ~TaskWidget();
    void initUI();
    void signalAndslots();
    void setlogconsole(QTextBrowser*);
    void reset();
public slots:
    virtual void onSelectBtn();
    virtual void onOkBtn();
    virtual void onCancelBtn();
    void oncurrentProcess(int value);
signals:
    void start();
    void quit();
protected:
    QLabel *numlabel;
    QPushButton *selectbtn;
    QPushButton *okbtn;
    QPushButton *cancelbtn;
    QProgressBar *bar;

    QStringList filelist;
    QTextBrowser *logconsole;
    Task *task;
    TaskManger *manager;
};
#endif // TASKWIDGET_H
