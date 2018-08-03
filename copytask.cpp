#include "copytask.h"

CopyTask::CopyTask(QObject *parent) : QObject(parent)
{

}

void CopyTask::setParmer(const QStringList& imagelist,const QString &path)
{
    this->imagelist = imagelist;
    this->distPath = path;
}

void CopyTask::doWork()
{
    qDebug()<<"void CopyTask::doWork()";
    int index = 0;
    for(auto file = imagelist.begin();file!=imagelist.end();file++)
    {
        QFile::copy(*file,this->distPath+"/"+QFileInfo(*file).fileName());
        emit msg(QString(tr("[%1]: cp %2 to %3")).arg(++index).arg(*file).arg(distPath+"/"));
    }
    emit resultReady();
}


TaskManger::TaskManger(CopyTask *task,QTextBrowser *logwidget)
{
    this->logwidget = logwidget;
    this->task = task;
    thread =new QThread(this);
    connect(thread,&QThread::finished,task,&CopyTask::deleteLater);
    connect(this, &TaskManger::run, task, &CopyTask::doWork);
    connect(task, &CopyTask::resultReady, this, &TaskManger::handleResults);
    connect(task,&CopyTask::msg,logwidget,&QTextBrowser::append);
    task->moveToThread(thread);
    thread->start();
}

TaskManger::~TaskManger()
{
    thread->quit();
    thread->wait();
}

void TaskManger::handleResults()
{
    task->msg("Task finished!");
}
