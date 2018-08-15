#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QtWidgets>

class Task:public QObject
{
    Q_OBJECT
public:
      virtual void setParmer(const QStringList& imagelist,const QString &path) = 0;
      virtual int getProcess()=0;
signals:
     void resultReady();
     void msg(const QString&);
     void currentProcess(int);
public slots:
      virtual void doWork()=0;
      virtual void stopWork() =0;
};


class CopyTask : public Task
{
    Q_OBJECT
public:
    CopyTask();
    void setParmer(const QStringList& imagelist,const QString &path);
    int getProcess();
public slots:
    void doWork();
    void stopWork();
private:
    QStringList imagelist;
    QString distPath;
    bool running;
    int currentprocess;
};


class RenameTask:public Task
{
    Q_OBJECT
public:
    RenameTask();
    void setParmer(const QStringList& imagelist,const QString &mode);
    int getProcess();
    void reset();
public slots:
    void doWork();
    void stopWork();
private:
    QStringList imagelist;
    QString mode;
    bool running;
    int currentprocess;
};

class VideoToImageTask:public Task
{
    Q_OBJECT
public:
    VideoToImageTask();
    void setParmer(const QStringList& videolist,const QString &path);
    int getProcess();
public slots:
    void doWork();
    void stopWork();
signals:

private:
    bool running;
    int currentprocess;
    QStringList videolist; //video list
    QString path; //save path
};


class TaskManger:public QObject
{
    Q_OBJECT
public:
    TaskManger(Task *task,QTextBrowser *logwidget = NULL);
    ~TaskManger();
    bool running();

public slots:
    void handleResults();
    void processValue(int);
private:
    QThread *thread;
    Task *task;
    QTextBrowser *logwidget;
signals:
      void currentProcess(int);
      void run();
      void stop();
};

#endif // TASK_H
