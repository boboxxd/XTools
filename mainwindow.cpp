#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr(""));
    initUI();
    signalAndslots();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initUI()
{
    widget1 = new SelectImageWidget;
    widget1->setlogconsle(ui->logconsole);
    ui->tabWidget->insertTab(0,widget1,"图片挑选 ");
    widget2 = new RenameImageWidget;
    widget2->setlogconsle(ui->logconsole);
    ui->tabWidget->insertTab(1,widget2,"图片重命名 ");

    widget3 = new VideoToImageWidget;
    widget3->setlogconsle(ui->logconsole);
    ui->tabWidget->insertTab(2,widget3,"视频转图片 ");
}

void MainWindow::signalAndslots()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(widget1)
    {
        delete widget1;
        widget1 = NULL;
    }

    if(widget2)
    {
        delete widget2;
        widget2 =NULL;
    }

    if(widget3)
    {
        delete widget3;
        widget3 =NULL;
    }
}


