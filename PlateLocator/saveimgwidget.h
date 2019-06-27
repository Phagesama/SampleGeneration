#ifndef SAVEIMGWIDGET_H
#define SAVEIMGWIDGET_H

#include <QWidget>
#include "saveimgthread.h"

namespace Ui {
class SaveImgWidget;
}

class SaveImgWidget : public QWidget
{
    Q_OBJECT
private slots:
    void updateProgress(int present);
    void threadFinished();

    void on_CancelButton_clicked();

    void on_OKButton_clicked();

public:
    explicit SaveImgWidget(QWidget *parent = nullptr);
    ~SaveImgWidget();

    void init(QStringList sourceImgNamesPara, QString savePathPara, QString rootPathPara,
                  int blur_Sizep, int sobel_Scalep, int sobel_Deltap,
                  int sobel_X_Weightp, int sobel_Y_Weightp,
                  int morph_Size_Widthp, int morph_Size_Heightp,
                  int minWidthp, int maxWidthp, int minHeightp, int maxHeightp,
                  float minRatiop, float maxRatiop,
                  int bluelow_Hp, int bluelow_Sp, int bluelow_Vp,
                  int blueup_Hp, int blueup_Sp, int blueup_Vp,
                  int yellowlow_Hp, int yellowlow_Sp, int yellowlow_Vp,
                  int yellowup_Hp, int yellowup_Sp, int yellowup_Vp);

private:
    QStringList sourceImgNames;
    QString savePath;
    QString rootPath;
    int blur_Size = 5;
    int sobel_Scale = 1;
    int sobel_Delta = 0;
    int sobel_X_Weight = 1;
    int sobel_Y_Weight = 0;
    int morph_Size_Width = 17;
    int morph_Size_Height = 3;
    int minWidth = 60;
    int maxWidth = 180;
    int minHeight = 18;
    int maxHeight = 80;
    float minRatio = 0.15f;
    float maxRatio = 0.70f;
    int bluelow_H = 100;
    int bluelow_S = 70;
    int bluelow_V = 70;
    int blueup_H = 140;
    int blueup_S = 255;
    int blueup_V = 255;
    int yellowlow_H = 15;
    int yellowlow_S = 70;
    int yellowlow_V = 70;
    int yellowup_H = 40;
    int yellowup_S = 255;
    int yellowup_V = 255;
    SaveImgThread *saveThread;

private:
    Ui::SaveImgWidget *ui;
};

#endif // SAVEIMGWIDGET_H
