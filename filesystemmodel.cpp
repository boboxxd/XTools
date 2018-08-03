#include "filesystemmodel.h"

bool isValid(const QString& str,const QString& mode)
{
    QRegExp re(mode);
    if(re.exactMatch(str))    //验证
    {
        return true;
    }
    else
    {
        return false;
    }
}

FileSystemModel::FileSystemModel(QObject *parent) : QFileSystemModel(parent)
{

}

int FileSystemModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


Qt::ItemFlags FileSystemModel::flags(const QModelIndex &index) const
{
    return QFileSystemModel::flags(index) | Qt::ItemIsUserCheckable;
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::CheckStateRole)
    {
        return checkedIndexes.contains(index) ? Qt::Checked : Qt::Unchecked;
    }
    else
    {
        return QFileSystemModel::data(index, role);
    }
}

bool FileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::CheckStateRole)
    {
        if(value == Qt::Checked)
        {
            checkedIndexes.insert(index);
            if(hasChildren(index) == true)
            {
                recursiveCheck(index, value);
            }
        }
        else
        {
            checkedIndexes.remove(index);
            if(hasChildren(index) == true)
            {
                recursiveCheck(index, value);
            }
        }
        emit dataChanged(index, index);
        return true;
    }
    return QFileSystemModel::setData(index, value, role);
}


QStringList FileSystemModel::checkedList(int type,const QString& filter) const
{
    QStringList checkedList;
    switch(type)
    {
    case 0:
        for(auto i =checkedIndexes.begin();i != checkedIndexes.end();i++)
        {
            QString path = this->filePath(*i);
            if(this->fileInfo(*i).isFile())
            {
                if(filter.trimmed().isEmpty())
                {
                    if(isValid(path,".*"))
                        checkedList.append(path);
                }else
                {
                    if(isValid(path,filter))
                        checkedList.append(path);
                }
            }

            if(this->fileInfo(*i).isDir())
            {

            }

        }
        break;
    case 1:
        for(auto i =checkedIndexes.begin();i != checkedIndexes.end();i++)
        {
            checkedList.append(this->fileName(*i));
        }
        break;
    }

    return checkedList;
}

bool FileSystemModel::recursiveCheck(const QModelIndex &index, const QVariant &value)
{
    if(hasChildren(index))
    {
        int i;
        int childrenCount = rowCount(index);
        QModelIndex child;
        for(i=0; i<childrenCount; i++)
        {
            child = QFileSystemModel::index(i, 0, index);
            setData(child, value, Qt::CheckStateRole);
        }
    }
}
