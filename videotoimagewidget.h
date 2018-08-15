#ifndef VIDEOTOIMAGE_H
#define VIDEOTOIMAGE_H

#include <QtWidgets>
#include "taskwidget.h"
namespace Ui {
class VideoToImageWidget;
}

class VideoToImageTaskWidget:public TaskWidget
{
    Q_OBJECT
public:
    VideoToImageTaskWidget(const QString& title ,QWidget *parent=NULL);
    ~VideoToImageTaskWidget();
    void closeEvent(QCloseEvent *event);
public slots:
    virtual void onSelectBtn();
    virtual void onOkBtn() override;
    virtual void onCancelBtn() override;
protected slots:
    void readmessage();
    void taskfinished(int,QProcess::ExitStatus);
protected:
    QTextBrowser *logconsole;
    QList<QProcess *> tasks;
    QString savePath;
    QString program;
    QStringList parma;
};

class VideoToImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VideoToImageWidget(QWidget *parent = 0);
    ~VideoToImageWidget();
    void setlogconsle(QTextBrowser *log);
    bool addTaskWidget(const QString &title);
    int taskMax();
    QTextBrowser *logWidget();
private:
    void setTaskWidgetsLayout();

private:
    Ui::VideoToImageWidget *ui;
    QTextBrowser *logconsole;
    QVector<VideoToImageTaskWidget*> taskwidgets;
    QGridLayout *layout;
};

#endif // VIDEOTOIMAGE_H
