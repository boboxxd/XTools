#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "filesystemmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initUI();
    void signalAndslots();
public slots:
    void onInBtn();
    void onOutBtn();
    void onstartTrans();
    void onClearBtn();
    void setTab1Filter(const QString &);
    void getSrcImagelist(const QModelIndex&);
    void getDirImagePath(const QModelIndex&);
    void setEndPath();
private:
    void updateListModel();
private:
    Ui::MainWindow *ui;
    QStringList currentpath;
    FileSystemModel *model;

    QStringList selectlist;
    QStringListModel *listmodel;
    QString tab1filter;
    QString tab1dirpath;

    QString savepath;
};

#endif // MAINWINDOW_H
