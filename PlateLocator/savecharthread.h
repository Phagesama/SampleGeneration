#ifndef SAVECHARTHREAD_H
#define SAVECHARTHREAD_H

#include <QThread>
#include <QFileDialog>
#include "platechar_svm.h"
#include "charsegment_v3.h"


class SaveCharThread : public QThread
{
    Q_OBJECT
signals:
    void progress(int present);

public:
    SaveCharThread();
    void init(QStringList sourcePlateNamesp,QString platesPathp,
              QString charsPathp,float gammaFactorp,
              int leftLimitp,int rightLimitp,
              int topLimitp,int bottomLimitp,
              int charminWidthp,int charmaxWidthp,
              int charminHeightp,int charmaxHeightp,
              float charminRatiop,float charmaxRatiop);

private:
    QString platesPath;
    QString charsPath;
    QStringList sourcePlateNames;
    float gammaFactor = 0.40f;
    int leftLimit = 0;
    int rightLimit = 0;
    int topLimit = 0;
    int bottomLimit = 0;
    int charminWidth = 2;
    int charmaxWidth = 30;
    int charminHeight = 10;
    int charmaxHeight = 80;
    float charminRatio = 0.08f;
    float charmaxRatio = 2.0f;

protected:
    virtual void run();
};

#endif // SAVECHARTHREAD_H
