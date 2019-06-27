#include "saveimgthread.h"

SaveImgThread::SaveImgThread()
{
}

void SaveImgThread::init(QStringList sourceImgNamesPara, QString savePathPara, QString rootPathPara,
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
}

void SaveImgThread::run()
{
    if (savePath == nullptr)
        return;
    if (rootPath == nullptr)
        return;
    if(sourceImgNames.empty())
        return;
    if (PlateCategory_SVM::PreparePlateTrainningDirectory(savePath) == false)
        return;
    int imgCount = 0;
    int sourceimgCount = sourceImgNames.length();
    for (int i = 0; i < sourceimgCount; i++)
    {
        emit progress((i * 1000) / sourceimgCount + 1);
        QString imgpath = rootPath + "/" + sourceImgNames[i];
        std::string str = imgpath.toLocal8Bit().toStdString();
        cv::Mat mat = cv::imread(str);
        cv::Mat matProcess;
        QList<PlateInfo> plateInfos = PlateLocator_V3::LocatePlatesForAutoSampleWithoutSVM(mat,&matProcess,blur_Size,sobel_Scale,sobel_Delta,sobel_X_Weight,sobel_Y_Weight,morph_Size_Width,morph_Size_Height,minWidth,maxWidth,minHeight,maxHeight,minRatio,maxRatio,bluelow_H,bluelow_S,bluelow_V,blueup_H,blueup_S,blueup_V,yellowlow_H,yellowlow_S,yellowlow_V,yellowup_H,yellowup_S,yellowup_V);
        for (PlateInfo plateInfo : plateInfos) {
            imgCount++;
            QString cuttedImgName = savePath + "/plates/未识别/" + QString::number(imgCount) + ".jpg";
            std::string str = cuttedImgName.toLocal8Bit().toStdString();
            cv::imwrite(str,plateInfo.originalMat);
        }
        plateInfos.clear();
    }
}
