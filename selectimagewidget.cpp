#include "selectimagewidget.h"
#include "ui_selectimagewidget.h"
#include "task.h"

SelectImageWidget::SelectImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectImageWidget)
{
    ui->setupUi(this);
    initUI();
    signalAndslots();
}

SelectImageWidget::~SelectImageWidget()
{
    delete ui;
}

void SelectImageWidget::initUI()
{
    ui->searchlineedit->setPlaceholderText(tr("输入过滤条件"));
    model = new FileSystemModel(this);
    model->setRootPath(QDir::rootPath());
    ui->srctreeview->setModel(model);

    selectlist =QStringList();
    listmodel = new QStringListModel(this);
    ui->dirlistview->setModel(listmodel);
}

void SelectImageWidget::signalAndslots()
{
    //pushbuttons
    connect(ui->inbtn,&QPushButton::clicked,this,&SelectImageWidget::onInBtn);
    connect(ui->outbtn,&QPushButton::clicked,this,&SelectImageWidget::onOutBtn);
    connect(ui->starttransbtn,&QPushButton::clicked,this,&SelectImageWidget::onstartTrans);
    connect(ui->clearbtn,&QPushButton::clicked,this,&SelectImageWidget::onClearBtn);
    //searchlineedit
    connect(ui->searchlineedit,&QLineEdit::textEdited,this,&SelectImageWidget::setTab1Filter);

    connect(ui->dirlineedit,&QLineEdit::textChanged,[this](QString txt){savepath = txt;qDebug()<<txt;});
    //treewidget
    connect(ui->srctreeview,&QTreeView::clicked,this,&SelectImageWidget::getSrcImagelist);

    //listView
    connect(ui->dirlistview,&QListView::clicked,this,&SelectImageWidget::getDirImagePath);
    connect(ui->dirlistview,&QListView::doubleClicked,this,&SelectImageWidget::previewImage);

    //dirbtn
    connect(ui->dirbtn,&QPushButton::clicked,this,&SelectImageWidget::setEndPath);
}

void SelectImageWidget::setlogconsle(QTextBrowser *log)
{
    this->logconsole = log;
}

void SelectImageWidget::onInBtn()
{
    selectlist= model->checkedList(0,tab1filter);
    updateListModel();
}

void SelectImageWidget::onOutBtn()
{
    QModelIndex index=ui->dirlistview->currentIndex();
    logconsole->append(QString("已移除：%1").arg(index.data(Qt::EditRole).toString()));
    selectlist.removeOne(index.data(Qt::EditRole).toString());
    updateListModel();
}

void SelectImageWidget::onstartTrans()
{

    Task *task =new CopyTask;
    task->setParmer(selectlist,savepath);
    TaskManger *manager = new TaskManger(task,logconsole);
    manager->run();
}

void SelectImageWidget::onClearBtn()
{
    selectlist.clear();
    updateListModel();
}

void SelectImageWidget::setTab1Filter(const QString &txt)
{
     logconsole->append(QString(tr("已设置过滤条件：%1")).arg(txt));
     tab1filter = txt;
}

void SelectImageWidget::getSrcImagelist(const QModelIndex &index)
{

}

void SelectImageWidget::getDirImagePath(const QModelIndex &index)
{

}

void SelectImageWidget::previewImage(const QModelIndex &index)
{
    QString pixname = index.data(Qt::EditRole).toString();
    if(QImage(pixname).isNull())
        return;

    ui->previewlabel->setPixmap(QPixmap::fromImage(QImage(pixname)).scaled(ui->previewlabel->size()));
}

void SelectImageWidget::setEndPath()
{
    QString savePath = QFileDialog::getExistingDirectory(this,
                                               tr("Choose Source Directory"),
                                               "./",
                                               QFileDialog::ShowDirsOnly);
   ui->dirlineedit->setText(savePath);
   if(!QDir(ui->dirlineedit->text()).exists())
   {
       QDir dir;
       dir.mkdir(this->savepath);
   }
}

void SelectImageWidget::updateListModel()
{
     listmodel->setStringList(selectlist);
     ui->statelabel->setText(tr("已选择: %1").arg(selectlist.count()));
}
