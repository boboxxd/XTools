#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "copytask.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    signalAndslots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//=========================tab_1========================================

void MainWindow::initUI()
{
    ui->searchlineedit->setPlaceholderText(tr("输入过滤条件"));
    model = new FileSystemModel(this);
    model->setRootPath(QDir::rootPath());
    ui->srctreeview->setModel(model);

    selectlist =QStringList();
    listmodel = new QStringListModel(this);
    ui->dirlistview->setModel(listmodel);
}

void MainWindow::signalAndslots()
{
    //pushbuttons
    connect(ui->inbtn,&QPushButton::clicked,this,&MainWindow::onInBtn);
    connect(ui->outbtn,&QPushButton::clicked,this,&MainWindow::onOutBtn);
    connect(ui->starttransbtn,&QPushButton::clicked,this,&MainWindow::onstartTrans);
    connect(ui->clearbtn,&QPushButton::clicked,this,&MainWindow::onClearBtn);
    //searchlineedit
    connect(ui->searchlineedit,&QLineEdit::textEdited,this,&MainWindow::setTab1Filter);

    connect(ui->dirlineedit,&QLineEdit::textChanged,[this](QString txt){savepath = txt;qDebug()<<txt;});
    //treewidget
    connect(ui->srctreeview,&QTreeView::clicked,this,&MainWindow::getSrcImagelist);

    //listView
    connect(ui->dirlistview,&QListView::clicked,this,&MainWindow::getDirImagePath);

    //dirbtn
    connect(ui->dirbtn,&QPushButton::clicked,this,&MainWindow::setEndPath);
}

void MainWindow::onInBtn()
{
    qDebug()<<"onInBtn";
    selectlist= model->checkedList(0,tab1filter);
    updateListModel();
}

void MainWindow::onOutBtn()
{
    qDebug()<<"onOutBtn";
    QModelIndex index=ui->dirlistview->currentIndex();
    ui->logconsole->append(QString("已移除：%1").arg(index.data(Qt::EditRole).toString()));
    selectlist.removeOne(index.data(Qt::EditRole).toString());
    updateListModel();
}

void MainWindow::onstartTrans()
{
    qDebug()<<"onstartTrans";
    CopyTask *task =new CopyTask;
    task->setParmer(selectlist,savepath);
    TaskManger *manager = new TaskManger(task,ui->logconsole);
    manager->run();
}

void MainWindow::onClearBtn()
{
    selectlist.clear();
    updateListModel();
}

void MainWindow::setTab1Filter(const QString &txt)
{
     ui->logconsole->append(QString(tr("已设置过滤条件：%1")).arg(txt));
     tab1filter = txt;
}

void MainWindow::getSrcImagelist(const QModelIndex &index)
{
    qDebug()<<model->filePath(index);
}

void MainWindow::getDirImagePath(const QModelIndex &index)
{
    qDebug()<<index.data(Qt::EditRole).toString();
}

void MainWindow::setEndPath()
{
    QString savePath = QFileDialog::getExistingDirectory(this,
                                               tr("Choose Source Directory"),
                                               "./",
                                               QFileDialog::ShowDirsOnly);
   ui->dirlineedit->setText(savePath);
   if(!QDir(ui->dirlineedit->text()).exists())
   {
       qDebug()<<"~~~~~~~~~~~";
       QDir dir;
       dir.mkdir(this->savepath);
   }
   //this->savepath = ui->dirlineedit->text();
}

void MainWindow::updateListModel()
{
     listmodel->setStringList(selectlist);
     ui->statelabel->setText(tr("已挑选: %1").arg(selectlist.count()));
}
