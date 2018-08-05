#ifndef RENAMEIMAGEWIDGET_H
#define RENAMEIMAGEWIDGET_H

#include <QtWidgets>
#include "task.h"
namespace Ui {
class RenameImageWidget;
}

class TaskWidget:public QGroupBox
{
    Q_OBJECT
public:
    TaskWidget(const QString& title ,QWidget *parent=NULL);
    ~TaskWidget();
    void initUI();
    void signalAndslots();
    void setlogconsole(QTextBrowser*);
    void reset();
public slots:
    void onSelectBtn();
    void onOkBtn();
    void onCancelBtn();
    void oncurrentProcess(int value);
signals:
    void start();
    void quit();
private:
    QLabel *numlabel;
    QPushButton *selectbtn;
    QPushButton *okbtn;
    QPushButton *cancelbtn;
    QProgressBar *bar;

    QStringList filelist;
    QTextBrowser *logconsole;
    Task *task;
    TaskManger *manager;
};

class RenameImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenameImageWidget(QWidget *parent = 0);
    ~RenameImageWidget();
    void setlogconsle(QTextBrowser *log);
     bool addTaskWidget(const QString &title);
    int taskMax();
private:
    void setTaskWidgetsLayout();
private:
    Ui::RenameImageWidget *ui;
    QTextBrowser *logconsole;
    QVector<TaskWidget*> taskwidgets;
    QGridLayout *layout;
};

#endif // RENAMEIMAGEWIDGET_H
