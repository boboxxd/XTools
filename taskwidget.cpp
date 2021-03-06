#include "taskwidget.h"

TaskWidget::TaskWidget(const QString &title, QWidget *parent)
{
    this->setTitle(title);
    this->resize(180,150);
    this->setParent(parent);
    setStyleSheet("TaskWidget{background-color:gray;}");
    logconsole = NULL;
    task = NULL;
    manager =NULL;
    initUI();
    signalAndslots();
}

TaskWidget::~TaskWidget()
{
    logconsole = NULL;
    if(task)
    {
        task = NULL;
    }

    if(manager)
    {
        delete manager;
        manager = NULL;
    }
}

void TaskWidget::initUI()
{
    numlabel = new QLabel();
    numlabel->setText("0");

    selectbtn = new QPushButton(tr("选择任务文件夹 "));
    okbtn = new QPushButton(tr("确定 "));
    cancelbtn = new QPushButton(tr("取消 "));
    reset();
    bar =new QProgressBar();
    bar->setValue(0);
    bar->setMaximum(100);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(selectbtn,0,0,1,4);
    layout->addWidget(new QLabel("文件数目: "),1,0,1,2);
    layout->addWidget(numlabel,1,2,1,2);
    layout->addWidget(new QLabel("进度: "),2,0,1,1);
    layout->addWidget(bar,2,1,1,3);
    layout->addWidget(okbtn,3,0,1,2);
    layout->addWidget(cancelbtn,3,2,1,2);
    this->setLayout(layout);
}

void TaskWidget::signalAndslots()
{
    connect(selectbtn,&QPushButton::clicked,this,&TaskWidget::onSelectBtn);
    connect(okbtn,&QPushButton::clicked,this,&TaskWidget::onOkBtn);
    connect(cancelbtn,&QPushButton::clicked,this,&TaskWidget::onCancelBtn);

}

void TaskWidget::setlogconsole(QTextBrowser *log)
{
    this->logconsole = log;
}

void TaskWidget::reset()
{
    selectbtn->setEnabled(true);
    okbtn->setEnabled(false);
    cancelbtn->setEnabled(false);
    filelist.clear();
}

void TaskWidget::onSelectBtn()
{
    bar->setValue(0);
    QString savePath = QFileDialog::getExistingDirectory(this,
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
    filter<<"*.JPG"<<"*.jpg"<<"*.jpeg"<<"*.JPEG"<<"*.png"<<"*.PNG";

    QStringList list = QDir(savePath).entryList(filter,QDir::Files,QDir::Name);
    foreach(QString name,list)
        filelist.append(savePath+"/"+name);
    numlabel->setText(QString("%1").arg(filelist.count()));
}

void TaskWidget::onOkBtn()
{
    task = new RenameTask;
    task->setParmer(filelist,"");
    manager = new TaskManger(task,logconsole);
    connect(manager,&TaskManger::currentProcess,this,&TaskWidget::oncurrentProcess);
    manager->run();
    cancelbtn->setEnabled(true);
}

void TaskWidget::onCancelBtn()
{
    manager->stop();
}

void TaskWidget::oncurrentProcess(int value)
{
    bar->setValue(value);
}



