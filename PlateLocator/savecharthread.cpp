#include "savecharthread.h"

SaveCharThread::SaveCharThread()
{

}

void SaveCharThread::init(QStringList sourcePlateNamesp, QString platesPathp,
                          QString charsPathp, float gammaFactorp,
                          int leftLimitp, int rightLimitp,
                          int topLimitp, int bottomLimitp,
                          int charminWidthp, int charmaxWidthp,
                          int charminHeightp, int charmaxHeightp,
                          float charminRatiop, float charmaxRatiop)
{
    sourcePlateNames = sourcePlateNamesp;
    platesPath = platesPathp;
    charsPath = charsPathp;
    gammaFactor = gammaFactorp;
    leftLimit = leftLimitp;
    rightLimit = rightLimitp;
    topLimit = topLimitp;
    bottomLimit = bottomLimitp;
    charminWidth = charminWidthp;
    charmaxWidth = charmaxWidthp;
    charminHeight = charminHeightp;
    charmaxHeight = charmaxHeightp;
    charminRatio = charminRatiop;
    charmaxRatio = charmaxRatiop;
}

void SaveCharThread::run()
{
    PlateChar_SVM::Load("./charRecog.xml");
    if (sourcePlateNames.empty())
        return;
    if (platesPath == nullptr)
        return;
    if (charsPath == nullptr)
        return;
    if (PlateChar_SVM::PrepareCharTrainningDirectory(charsPath) == false)
        return;
    int charCount = 0;
    int sourcePlateCount = sourcePlateNames.length();
    for (int i = 0;i < sourcePlateCount;i++)
    {
        emit progress((i * 1000) / sourcePlateCount + 1);
        QString platePath = platesPath + "/plates/普通车牌/" + sourcePlateNames[i];
        std::string str = platePath.toLocal8Bit().toStdString();
        cv::Mat mat = cv::imread(str);
        QList<CharInfo> charInfos = CharSegment_V3::SplitPlateForAutoSampleWithAllPara(mat,gammaFactor,leftLimit,rightLimit,
                                                                                       topLimit,bottomLimit,charminWidth,charmaxWidth,
                                                                                       charminHeight,charmaxHeight,charminRatio,charmaxRatio);
        for (CharInfo charInfo : charInfos)
        {
            charCount++;
            QString cuttedCharName = charsPath + "/chars/未识别字符/" + QString::number(charCount) + ".jpg";
            std::string str = cuttedCharName.toLocal8Bit().toStdString();
            cv::imwrite(str,charInfo.originalMat);
        }
        charInfos.clear();
    }
}
