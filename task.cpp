#include "task.h"

CopyTask::CopyTask()
{
    running = false;
    currentprocess =0;
}

void CopyTask::setParmer(const QStringList& imagelist,const QString &path)
{
    this->imagelist = imagelist;
    this->distPath = path;
}

int CopyTask::getProcess()
{
    return currentprocess;
}

void CopyTask::doWork()
{
    running =true;
    currentprocess = 0;
    for(auto file = imagelist.begin();file!=imagelist.end();file++)
    {
        if(!running)
            break;
        QFile::copy(*file,this->distPath+"/"+QFileInfo(*file).fileName());
        emit msg(QString(tr("[%1]: cp %2 to %3")).arg(++currentprocess).arg(*file).arg(distPath+"/"));
    }
    emit resultReady();
}

void CopyTask::stopWork()
{
    running =false;
}

//---------------------------------------------------------------------------------
TaskManger::TaskManger(Task *task,QTextBrowser *logwidget)
{
    this->logwidget = logwidget;
    this->task = task;
    thread =new QThread(this);
    connect(thread,&QThread::finished,task,&Task::deleteLater);
    connect(this, &TaskManger::run, task, &Task::doWork);
    connect(this,&TaskManger::stop,task,&Task::stopWork);
    connect(task, &Task::resultReady, this, &TaskManger::handleResults);
    connect(task,&Task::msg,logwidget,&QTextBrowser::append);

    connect(task,&Task::currentProcess,this,&TaskManger::processValue);
    task->moveToThread(thread);
    thread->start();
}

TaskManger::~TaskManger()
{
    thread->quit();
    thread->wait();
}

bool TaskManger::running()
{
    return thread->isRunning();
}

void TaskManger::processValue(int value)
{
    emit currentProcess(value);
}

void TaskManger::handleResults()
{
    task->msg("Task finished!");
}

//----------------------------------------------------------------------------------
RenameTask::RenameTask()
{
    running = false;
    currentprocess =0;
}

void RenameTask::setParmer(const QStringList &imagelist, const QString &mode)
{
    this->imagelist = imagelist;
    this->mode = mode;
}

int RenameTask::getProcess()
{
    return currentprocess;
}

void RenameTask::reset()
{
    running = false;
    currentprocess = 0;
}


void RenameTask::doWork()
{
    running = true;
    currentprocess = 0;
    for(auto file = imagelist.begin();file!=imagelist.end();file++)
    {
        if(!running)
            break;
        QString newname = QDateTime::currentDateTime().toString("yyyyMMddhhmmss%1.jpg").arg(++currentprocess,5,10,QLatin1Char('0'));
        QDir().rename(*file,QFileInfo(*file).absolutePath()+"/"+newname);
        emit msg(QString(tr("[%1]: rename %2 to %3")).arg(currentprocess).arg(*file).arg(QFileInfo(*file).absolutePath()+"/"+newname));
        emit currentProcess((currentprocess*1.0/imagelist.count())*100);
    } 
    emit resultReady();
}

void RenameTask::stopWork()
{
    running =false;
}

//---------------------------------------------------------------------
VideoToImageTask::VideoToImageTask()
{
    running = false;
    currentprocess =0;
}

void VideoToImageTask::setParmer(const QStringList &videolist, const QString &path)
{

}

int VideoToImageTask::getProcess()
{
    return currentprocess;
}

void VideoToImageTask::doWork()
{

}

void VideoToImageTask::stopWork()
{

}
