#ifndef RENAMEIMAGEWIDGET_H
#define RENAMEIMAGEWIDGET_H

#include <QtWidgets>
#include "task.h"
#include "taskwidget.h"
namespace Ui {
class RenameImageWidget;
}



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
