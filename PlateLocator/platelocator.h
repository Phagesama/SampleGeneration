#ifndef PLATELOCATOR_H
#define PLATELOCATOR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QThread>
#include <QCheckBox>
#include <QTableWidgetItem>

#include "platelocator_v3.h"
#include "matswitch.h"
#include "saveimgwidget.h"
#include "showplatethread.h"

namespace Ui {
class PlateLocator;
}

class PlateLocator : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlateLocator(QWidget *parent = nullptr);
    ~PlateLocator();

private slots:
    void updateResList(QListWidgetItem *item);

    void on_inputButton_clicked();

    void on_fileList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_blur_Size_valueChanged(int arg1);

    void on_bluelow_H_valueChanged(int arg1);

    void on_bluelow_S_valueChanged(int arg1);

    void on_bluelow_V_valueChanged(int arg1);

    void on_blueup_H_valueChanged(int arg1);

    void on_blueup_S_valueChanged(int arg1);

    void on_blueup_V_valueChanged(int arg1);

    void on_yellowlow_H_valueChanged(int arg1);

    void on_yellowlow_S_valueChanged(int arg1);

    void on_yellowlow_V_valueChanged(int arg1);

    void on_yellowup_H_valueChanged(int arg1);

    void on_yellowup_S_valueChanged(int arg1);

    void on_yellowup_V_valueChanged(int arg1);

    void on_sobel_Scale_valueChanged(int arg1);

    void on_sobel_Delta_valueChanged(int arg1);

    void on_sobel_X_Weight_valueChanged(int arg1);

    void on_sobel_Y_Weight_valueChanged(int arg1);

    void on_morph_SIze_Width_valueChanged(int arg1);

    void on_morph_Size_Height_valueChanged(int arg1);

    void on_minWidth_valueChanged(int arg1);

    void on_maxWidth_valueChanged(int arg1);

    void on_minHeight_valueChanged(int arg1);

    void on_maxHeight_valueChanged(int arg1);

    void on_minRatio_valueChanged(double arg1);

    void on_maxRatio_valueChanged(double arg1);

    void on_outputButton_clicked();

    void on_sourcePlate_clicked();

    void on_showClass_currentTextChanged(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_moveButton_clicked();

    void on_autoClassify_clicked();

    void on_centralTab_tabBarClicked(int index);

    void on_simpleXML_clicked();

private:
    void updatapara();
    void showCutedImage();
    void showSourcePlate();

public:
    QString rootPath;
    QString savePath;
    QStringList sourceImgNames;
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
    SaveImgWidget *saveImgWidget;
    ShowPlateThread *showPlateThread = nullptr;

private:
    Ui::PlateLocator *ui;
    bool imgSaved = false;
};

#endif // PLATELOCATOR_H
