#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "filesystemmodel.h"
#include "selectimagewidget.h"
#include "renameimagewidget.h"
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
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;

    SelectImageWidget *widget1;
    RenameImageWidget *widget2;
};

#endif // MAINWINDOW_H
