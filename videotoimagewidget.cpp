#include "videotoimagewidget.h"
#include "ui_videotoimagewidget.h"
#include <QMutex>
QMutex mutex;

static bool mkdir(const QString& name)
{
    QDir dir(name);
    if(dir.exists())
        return true;
    else
        return dir.mkdir(name);
}


VideoToImageTaskWidget::VideoToImageTaskWidget(const QString &title, QWidget *parent)
    :TaskWidget(title,parent)
{
#if defined(Q_OS_UNIX)
    program="3rdpart/unix/ffmpeg/ffmpeg.sh";
#else
    program="3rdpart/win32/ffmpeg/ffmpeg.exe";
#endif
    tasks.clear();
    logconsole=qobject_cast<VideoToImageWidget*>(parentWidget())->logWidget();
}

VideoToImageTaskWidget::~VideoToImageTaskWidget()
{

}

void VideoToImageTaskWidget::closeEvent(QCloseEvent *event)
{
    if(!tasks.isEmpty())
    {
        int re = QMessageBox::warning(this,tr("warning"),tr("有任务在运行，是否强制退出？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
        if(re == 1)
        {
            onCancelBtn();
        }else
        {
            return;
        }
    }
}

void VideoToImageTaskWidget::onSelectBtn()
{
    bar->setValue(0);
    filelist.clear();
    tasks.clear();
    savePath = QFileDialog::getExistingDirectory(this,
                                                 tr("Choose Source Directory"),
                                                 "./",
                                                 QFileDialog::ShowDirsOnly);
    if(savePath.isEmpty())
    {
        reset();
        return;
    }

    this->setTitle(QString(tr("Task: %1")).arg(savePath));
    okbtn->setEnabled(true);
    cancelbtn->setEnabled(false);

    QStringList filter;
    filter<<"*.MP4"<<"*.mp4"<<"*.MOV"<<"*.mov"<<"*.MKV"<<"*.mkv";

    QStringList list = QDir(savePath).entryList(filter,QDir::Files,QDir::Name);
    foreach(QString name,list)
        filelist.append(savePath+"/"+name);
    numlabel->setText(QString("%1").arg(filelist.count()));
}

void VideoToImageTaskWidget::onOkBtn()
{
    int index = 0;
    this->cancelbtn->setEnabled(true);
    for(auto video=filelist.begin();video != filelist.end();video++)
    {
        ++index;
        bar->setValue(float(index)/filelist.count()*100);
        QString resultimagepath=savePath+"/output/";
        mkdir(resultimagepath);
#if defined(Q_OS_UNIX)
        parma<<*video<<"1"<<resultimagepath+QString::number(index)+"_%05d.jpg";
#else
        parma<<"-i"<<*video<<"-r"<<"1"<<savePath+"/output/"+QString::number(index)+"_%05d.jpg";
#endif

        QProcess *process=new QProcess;
        process->setReadChannelMode(QProcess::MergedChannels);
        connect(process,&QProcess::readyReadStandardOutput,this,&VideoToImageTaskWidget::readmessage);
        connect(process,&QProcess::readyReadStandardError,this,&VideoToImageTaskWidget::readmessage);

        connect(process,static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),this,&VideoToImageTaskWidget::taskfinished);
        process->start(program,parma);
        tasks.append(process);
        parma.clear();
    }
}

void VideoToImageTaskWidget::onCancelBtn()
{
    for(auto task=tasks.begin();task!=tasks.end();task++)
    {
        if(*task)
        {
            (*task)->close();
            delete (*task);
        }
    }
    tasks.clear();
}

void VideoToImageTaskWidget::readmessage()
{
    for(auto task=tasks.begin();task!=tasks.end();task++)
    {
        mutex.lock();
        logconsole->append((*task)->readAllStandardOutput());
        mutex.unlock();
    }
}

void VideoToImageTaskWidget::taskfinished(int code, QProcess::ExitStatus)
{
    switch(code){
    case QProcess::NormalExit:
        logconsole->append("Task finished !");
        break;
    case QProcess::CrashExit:
        logconsole->append("Task Termintered !");
    }
}

//-----------------------------------------------------------------

VideoToImageWidget::VideoToImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoToImageWidget)
{
    ui->setupUi(this);
    logconsole = NULL;
    layout = new QGridLayout();
    setLayout(layout);
}


QTextBrowser* VideoToImageWidget::logWidget()
{
    return logconsole;
}


VideoToImageWidget::~VideoToImageWidget()
{
    delete ui;
}

void VideoToImageWidget::setlogconsle(QTextBrowser *log)
{
    this->logconsole = log;
    addTaskWidget("task1");
    addTaskWidget("task2");
    addTaskWidget("task3");
    addTaskWidget("task4");
    addTaskWidget("task5");
    addTaskWidget("task6");
    addTaskWidget("task7");
    addTaskWidget("task8");
    addTaskWidget("task9");
    addTaskWidget("task10");
    addTaskWidget("task11");
    addTaskWidget("task12");
}

bool VideoToImageWidget::addTaskWidget(const QString &title)
{
    if(taskwidgets.count() >= taskMax())
    {
        logconsole->append(QString("任务数已达上限！"));
        return false;
    }

    VideoToImageTaskWidget *task = new VideoToImageTaskWidget(title,this);
    if(logconsole)
    {
        task->setlogconsole(logconsole);
    }
    taskwidgets.push_back(task);
    setTaskWidgetsLayout();
    return true;
}

int VideoToImageWidget::taskMax()
{
    return (width()/200)*(height()/160);
}



void VideoToImageWidget::setTaskWidgetsLayout()
{
    int startx=0,starty=0;
    for(auto widget=taskwidgets.begin();widget != taskwidgets.end();widget++)
    {
        if(starty >(height()/160))
        {
            startx++;
            starty=0;
        }
        layout->addWidget(*widget,startx,starty++,1,1);
    }
}
