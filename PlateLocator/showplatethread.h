#ifndef SHOWPLATETHREAD_H
#define SHOWPLATETHREAD_H

#include <QThread>
#include <QPixmap>
#include <QDir>
#include <QListWidgetItem>
#include <QCheckBox>

#include "matswitch.h"

class ShowPlateThread : public QThread
{
    Q_OBJECT
signals:
    void getPixmap(QListWidgetItem *item);

public:
    ShowPlateThread();
    void init(QString classPath);

private:
    QString path;

protected:
    virtual void run();
};

#endif // SHOWPLATETHREAD_H
