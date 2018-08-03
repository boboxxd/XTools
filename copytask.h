#ifndef COPYTASK_H
#define COPYTASK_H

#include <QObject>
#include <QtWidgets>
class CopyTask : public QObject
{
    Q_OBJECT
public:
    explicit CopyTask(QObject *parent = nullptr);   
    void setParmer(const QStringList& imagelist,const QString &path);

signals:
    void resultReady();
    void msg(const QString&);
public slots:
    void doWork();


private:
    QStringList imagelist;
    QString distPath;
};


class TaskManger:public QObject
{
    Q_OBJECT
public:
    TaskManger(CopyTask *task,QTextBrowser *logwidget = NULL);
    ~TaskManger();
public slots:
    void handleResults();
private:
    QThread *thread;
    CopyTask *task;
    QTextBrowser *logwidget;
signals:
      void run();
};

#endif // COPYTASK_H
