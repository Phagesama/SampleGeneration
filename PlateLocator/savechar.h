#ifndef SAVECHAR_H
#define SAVECHAR_H

#include <QWidget>
#include "savecharthread.h"

namespace Ui {
class SaveChar;
}

class SaveChar : public QWidget
{
    Q_OBJECT
private slots:
    void updateProgress(int present);

    void threadFinished();

    void on_OKButton_clicked();

    void on_CancelButton_clicked();

public:
    explicit SaveChar(QWidget *parent = nullptr);
    ~SaveChar();
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
    SaveCharThread *saveCharThread;

private:
    Ui::SaveChar *ui;
};

#endif // SAVECHAR_H
