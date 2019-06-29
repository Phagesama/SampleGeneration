#include "showcharthread.h"
#include <Windows.h>

ShowCharThread::ShowCharThread()
{

}

void ShowCharThread::init(QString classPath)
{
    path = classPath;
}

void ShowCharThread::run()
{
    QDir* classdir = new QDir(path);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";
    QStringList sourceCharNames = classdir->entryList(nameFilters);
    int sourceCharCount = sourceCharNames.size();
    for (int i = 0;i < sourceCharCount;i++)
    {
        QString charPath = path + "/" + sourceCharNames[i];
        QPixmap charpm = QPixmap(charPath).scaled(80,160);
        QListWidgetItem *item = new QListWidgetItem(QIcon(charpm),"");
        item->setWhatsThis(sourceCharNames[i]);
        emit getPixmap(item);
        Sleep(50);
    }
}
