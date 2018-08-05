#ifndef SELECTIMAGEWIDGET_H
#define SELECTIMAGEWIDGET_H

#include <QtWidgets>
#include "filesystemmodel.h"


namespace Ui {
class SelectImageWidget;
}

class SelectImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectImageWidget(QWidget *parent = 0);
    ~SelectImageWidget();

    void initUI();
    void signalAndslots();
    void setlogconsle(QTextBrowser *log);
public slots:
    void onInBtn();
    void onOutBtn();
    void onstartTrans();
    void onClearBtn();
    void setTab1Filter(const QString &);
    void getSrcImagelist(const QModelIndex&);
    void getDirImagePath(const QModelIndex&);
    void previewImage(const QModelIndex&);
    void setEndPath();
private:
    void updateListModel();

private:
    Ui::SelectImageWidget *ui;

    QStringList currentpath;
    FileSystemModel *model;

    QStringList selectlist;
    QStringListModel *listmodel;
    QString tab1filter;
    QString tab1dirpath;

    QString savepath;
    QTextBrowser *logconsole;
};

#endif // SELECTIMAGEWIDGET_H
