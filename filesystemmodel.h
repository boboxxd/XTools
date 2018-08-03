#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QtWidgets>
class FileSystemModel : public QFileSystemModel
{
public:
    FileSystemModel(QObject *parent=NULL);
    //第1列显示名称，其他几列都屏蔽掉
    int columnCount(const QModelIndex &parent) const;
    QSet<QPersistentModelIndex> checkedIndexes;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QStringList checkedList(int type,const QString& filter) const;
private:
    bool recursiveCheck(const QModelIndex &index, const QVariant &value);

};

#endif // FILESYSTEMMODEL_H
