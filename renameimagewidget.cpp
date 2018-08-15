#include "renameimagewidget.h"
#include "ui_renameimagewidget.h"
#include "task.h"
#include <QtConcurrent/QtConcurrent>

RenameImageWidget::RenameImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenameImageWidget)
{
    ui->setupUi(this);
    logconsole = NULL;
    layout = new QGridLayout();
    setLayout(layout);


}

RenameImageWidget::~RenameImageWidget()
{
    for(auto widget=taskwidgets.begin();widget != taskwidgets.end();widget++)
    {
        delete *widget;
    }
    delete ui;
}

void RenameImageWidget::setlogconsle(QTextBrowser *log)
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

bool RenameImageWidget::addTaskWidget(const QString &title)
{
    if(taskwidgets.count() >= taskMax())
    {
        logconsole->append(QString("任务数已达上限！"));
        return false;
    }

    TaskWidget *task = new TaskWidget(title,this);
    if(logconsole)
    {
        task->setlogconsole(logconsole);
    }
    taskwidgets.push_back(task);
    setTaskWidgetsLayout();
    return true;
}

int RenameImageWidget::taskMax()
{
    return (width()/200)*(height()/160);
}

void RenameImageWidget::setTaskWidgetsLayout()
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


