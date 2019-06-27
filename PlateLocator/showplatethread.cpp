#include "showplatethread.h"
#include <Windows.h>

ShowPlateThread::ShowPlateThread()
{

}

void ShowPlateThread::init(QString classPath)
{
    path = classPath;
}

void ShowPlateThread::run()
{
    QDir* classdir = new QDir(path);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";
    QStringList sourcePlateNames = classdir->entryList(nameFilters);
    int sourcePlateCount = sourcePlateNames.size();
    for (int i = 0;i < sourcePlateCount;i++)
    {
        QString platePath = path + "/" + sourcePlateNames[i];
        QPixmap platepm = QPixmap(platePath).scaled(180,80);
        QListWidgetItem *item = new QListWidgetItem(QIcon(platepm),"");
        item->setWhatsThis(sourcePlateNames[i]);
        emit getPixmap(item);
        Sleep(50);
    }
}
