#ifndef SHOWCHARTHREAD_H
#define SHOWCHARTHREAD_H

#include <QThread>
#include <QPixmap>
#include <QDir>
#include <QListWidgetItem>
#include <QCheckBox>

#include "matswitch.h"

class ShowCharThread : public QThread
{
    Q_OBJECT
signals:
    void getPixmap(QListWidgetItem *item);

public:
    ShowCharThread();
    void init(QString classPath);

private:
    QString path;

protected:
    virtual void run();

};

#endif // SHOWCHARTHREAD_H
