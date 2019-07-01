#include "saveimgwidget.h"
#include "ui_saveimgwidget.h"

SaveImgWidget::SaveImgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveImgWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("Saving");
    ui->OKButton->setEnabled(false);
    saveThread = new SaveImgThread();
    connect(saveThread,&SaveImgThread::progress,this,&SaveImgWidget::updateProgress);
    connect(saveThread,&SaveImgThread::finished,this,&SaveImgWidget::threadFinished);
}

SaveImgWidget::~SaveImgWidget()
{
    delete ui;
}

void SaveImgWidget::updateProgress(int present)
{
    ui->progressBar->setValue(present);
}

void SaveImgWidget::threadFinished()
{
    ui->progressBar->setValue(1000);
    ui->OKButton->setEnabled(true);
}

void SaveImgWidget::init(QStringList sourceImgNamesPara, QString savePathPara, QString rootPathPara,
                         int blur_Sizep, int sobel_Scalep, int sobel_Deltap,
                         int sobel_X_Weightp, int sobel_Y_Weightp,
                         int morph_Size_Widthp, int morph_Size_Heightp,
                         int minWidthp, int maxWidthp,
                         int minHeightp, int maxHeightp,
                         float minRatiop, float maxRatiop,
                         int bluelow_Hp, int bluelow_Sp, int bluelow_Vp,
                         int blueup_Hp, int blueup_Sp, int blueup_Vp,
                         int yellowlow_Hp, int yellowlow_Sp, int yellowlow_Vp,
                         int yellowup_Hp, int yellowup_Sp, int yellowup_Vp)
{
    sourceImgNames = sourceImgNamesPara;
    savePath = savePathPara;
    rootPath = rootPathPara;
    blur_Size = blur_Sizep;
    sobel_Scale = sobel_Scalep;
    sobel_Delta = sobel_Deltap;
    sobel_X_Weight = sobel_X_Weightp;
    sobel_Y_Weight = sobel_Y_Weightp;
    morph_Size_Width = morph_Size_Widthp;
    morph_Size_Height = morph_Size_Heightp;
    minWidth = minWidthp;
    maxWidth = maxWidthp;
    minHeight = minHeightp;
    maxHeight = maxHeightp;
    minRatio = minRatiop;
    maxRatio = maxRatiop;
    bluelow_H = bluelow_Hp;
    bluelow_S = bluelow_Sp;
    bluelow_V = bluelow_Vp;
    blueup_H = blueup_Hp;
    blueup_S = blueup_Sp;
    blueup_V = blueup_Vp;
    yellowlow_H = yellowlow_Hp;
    yellowlow_S = yellowlow_Sp;
    yellowlow_V = yellowlow_Vp;
    yellowup_H = yellowup_Hp;
    yellowup_S = yellowup_Sp;
    yellowup_V = yellowup_Vp;

    saveThread->init(sourceImgNames,savePath,rootPath,
                     blur_Size,sobel_Scale,sobel_Delta,
                     sobel_X_Weight,sobel_Y_Weight,
                     morph_Size_Width,morph_Size_Height,
                     minWidth,maxWidth,
                     minHeight,maxHeight,
                     minRatio,maxRatio,
                     bluelow_H,bluelow_S,bluelow_V,
                     blueup_H,blueup_S,blueup_V,
                     yellowlow_H,yellowlow_S,yellowlow_V,
                     yellowup_H,yellowup_S,yellowup_V);
    saveThread->start();
}

void SaveImgWidget::on_CancelButton_clicked()
{
    saveThread->terminate();
    ui->OKButton->setEnabled(true);
    this->destroy();
}

void SaveImgWidget::on_OKButton_clicked()
{
    this->destroy();
}
