#include "platelocator.h"
#include "ui_platelocator.h"

PlateLocator::PlateLocator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlateLocator)
{
    ui->setupUi(this);
    this->setWindowTitle("样本生成");
    updatapara();
    saveImgWidget = new SaveImgWidget();
}

PlateLocator::~PlateLocator()
{
    delete ui;
}

void PlateLocator::updatapara()
{
    blur_Size = ui->blur_Size->value();
    blur_Size += blur_Size % 2 - 1;
    sobel_Scale = ui->sobel_Scale->value();
    sobel_Delta = ui->sobel_Delta->value();
    sobel_X_Weight = ui->sobel_X_Weight->value();
    sobel_Y_Weight = ui->sobel_Y_Weight->value();
    morph_Size_Width = ui->morph_SIze_Width->value();
    morph_Size_Width += morph_Size_Width % 2 - 1;
    morph_Size_Height = ui->morph_Size_Height->value();
    morph_Size_Height += morph_Size_Height % 2 - 1;
    minWidth = ui->minWidth->value();
    maxWidth = ui->maxWidth->value();
    minHeight = ui->minHeight->value();
    maxHeight = ui->maxHeight->value();
    minRatio = ui->minRatio->value();
    maxRatio = ui->maxRatio->value();
    bluelow_H = ui->bluelow_H->value();
    bluelow_S = ui->bluelow_S->value();
    bluelow_V = ui->bluelow_V->value();
    blueup_H = ui->blueup_H->value();
    blueup_S = ui->blueup_S->value();
    blueup_V = ui->blueup_V->value();
    yellowlow_H = ui->yellowlow_H->value();
    yellowlow_S = ui->yellowlow_S->value();
    yellowlow_V = ui->yellowlow_V->value();
    yellowup_H = ui->yellowup_H->value();
    yellowup_S = ui->yellowup_S->value();
    yellowup_V = ui->yellowup_V->value();
}

void PlateLocator::showCutedImage()
{
    ui->cuttedImgList->clear();
    ui->cuttedImgList->setIconSize(QSize(180,80));
    QString imgpath = rootPath + "/" + ui->fileList->currentItem()->text();
    std::string str = imgpath.toLocal8Bit().toStdString();
    cv::Mat mat = cv::imread(str);
    cv::Mat matProcess;
    QList<PlateInfo> plateInfos = PlateLocator_V3::LocatePlatesForAutoSampleWithoutSVM(mat,&matProcess,
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
    QPixmap imgsource = MatSwitch::Mat2QPixmap(mat).scaled(1280,720);
    QPixmap imgprocess = MatSwitch::Mat2QPixmap(matProcess,QImage::Format_Grayscale8).scaled(1280,720);
    ui->sourceImgLabel->setPixmap(imgsource);
    ui->processImgLabel->setPixmap(imgprocess);
    for (PlateInfo plateInfo : plateInfos) {
        QPixmap plate = MatSwitch::Mat2QPixmap(plateInfo.originalMat).scaled(180,80);
        QListWidgetItem *plateitem = new QListWidgetItem(QIcon(plate),"");
        ui->cuttedImgList->addItem(plateitem);
    }
}

void PlateLocator::showSourcePlate()
{
    QString classPath = savePath + "/plates/" + ui->showClass->currentText();
    ui->resList->clear();
    ui->resList->setIconSize(QSize(180,80));
    if (showPlateThread != nullptr)
    {
        showPlateThread->terminate();
        showPlateThread->destroyed();
    }
    showPlateThread = new ShowPlateThread();
    connect(showPlateThread,&ShowPlateThread::getPixmap,this,&PlateLocator::updateResList);
    showPlateThread->init(classPath);
    showPlateThread->start();
}

void PlateLocator::updateResList(QListWidgetItem *item)
{
    QCheckBox *platecb = new QCheckBox();
    platecb->setCheckable(true);
    ui->resList->addItem(item);
    ui->resList->setItemWidget(item,platecb);
}

void PlateLocator::on_inputButton_clicked()
{
    rootPath = QFileDialog::getExistingDirectory(this, "选择图片所在文件夹", "E:/");
    if (rootPath.isEmpty())
        return;
    ui->fileList->clear();
    QDir* rootdir = new QDir(rootPath);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";
    sourceImgNames = rootdir->entryList(nameFilters);
    for (QString sourceImgName : sourceImgNames)
    {
        ui->fileList->addItem(sourceImgName);
    }
    ui->fileList->setCurrentRow(0);
    showCutedImage();
}

void PlateLocator::on_outputButton_clicked()
{
    savePath = QFileDialog::getExistingDirectory(this, "选择车牌样本存储路径", "E:/");
    if (savePath.isEmpty())
        return;
    saveImgWidget->init(sourceImgNames,savePath,rootPath,
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
    saveImgWidget->show();
    imgSaved = true;
}

void PlateLocator::on_sourcePlate_clicked()
{
    savePath = QFileDialog::getExistingDirectory(this, "选择车牌样本存储路径", "E:/");
    if (savePath.isEmpty())
        return;
    showSourcePlate();
}

void PlateLocator::on_fileList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    showCutedImage();
}

void PlateLocator::on_blur_Size_valueChanged(int arg1)
{
    blur_Size = arg1;
    showCutedImage();
}

void PlateLocator::on_bluelow_H_valueChanged(int arg1)
{
    bluelow_H = arg1;
    showCutedImage();
}

void PlateLocator::on_bluelow_S_valueChanged(int arg1)
{
    bluelow_S = arg1;
    showCutedImage();
}

void PlateLocator::on_bluelow_V_valueChanged(int arg1)
{
    bluelow_V = arg1;
    showCutedImage();
}

void PlateLocator::on_blueup_H_valueChanged(int arg1)
{
    blueup_H = arg1;
    showCutedImage();
}

void PlateLocator::on_blueup_S_valueChanged(int arg1)
{
    blueup_S = arg1;
    showCutedImage();
}

void PlateLocator::on_blueup_V_valueChanged(int arg1)
{
    blueup_V = arg1;
    showCutedImage();
}

void PlateLocator::on_yellowlow_H_valueChanged(int arg1)
{
    yellowlow_H = arg1;
    showCutedImage();
}

void PlateLocator::on_yellowlow_S_valueChanged(int arg1)
{
    yellowlow_S = arg1;
    showCutedImage();
}

void PlateLocator::on_yellowlow_V_valueChanged(int arg1)
{
    yellowlow_V = arg1;
    showCutedImage();
}

void PlateLocator::on_yellowup_H_valueChanged(int arg1)
{
    yellowup_H = arg1;
    showCutedImage();
}

void PlateLocator::on_yellowup_S_valueChanged(int arg1)
{
    yellowup_S = arg1;
    showCutedImage();
}

void PlateLocator::on_yellowup_V_valueChanged(int arg1)
{
    yellowup_V = arg1;
    showCutedImage();
}

void PlateLocator::on_sobel_Scale_valueChanged(int arg1)
{
    sobel_Scale = arg1;
    showCutedImage();
}

void PlateLocator::on_sobel_Delta_valueChanged(int arg1)
{
    sobel_Delta = arg1;
    showCutedImage();
}

void PlateLocator::on_sobel_X_Weight_valueChanged(int arg1)
{
    sobel_X_Weight = arg1;
    showCutedImage();
}

void PlateLocator::on_sobel_Y_Weight_valueChanged(int arg1)
{
    sobel_Y_Weight = arg1;
    showCutedImage();
}

void PlateLocator::on_morph_SIze_Width_valueChanged(int arg1)
{
    morph_Size_Width = arg1;
    showCutedImage();
}

void PlateLocator::on_morph_Size_Height_valueChanged(int arg1)
{
    morph_Size_Height = arg1;
    showCutedImage();
}

void PlateLocator::on_minWidth_valueChanged(int arg1)
{
    minWidth = arg1;
    showCutedImage();
}

void PlateLocator::on_maxWidth_valueChanged(int arg1)
{
    maxWidth = arg1;
    showCutedImage();
}

void PlateLocator::on_minHeight_valueChanged(int arg1)
{
    minHeight = arg1;
    showCutedImage();
}

void PlateLocator::on_maxHeight_valueChanged(int arg1)
{
    maxHeight = arg1;
    showCutedImage();
}

void PlateLocator::on_minRatio_valueChanged(double arg1)
{
    minRatio = arg1;
    showCutedImage();
}

void PlateLocator::on_maxRatio_valueChanged(double arg1)
{
    maxRatio = arg1;
    showCutedImage();
}

void PlateLocator::on_showClass_currentTextChanged(const QString &arg1)
{
    showSourcePlate();
}

void PlateLocator::on_checkBox_stateChanged(int arg1)
{
    int count = ui->resList->count();
    for (int i = 0;i < count;i++)
    {
        QListWidgetItem *item = ui->resList->item(i);
        QWidget *widget = ui->resList->itemWidget(item);
        QCheckBox *box = (QCheckBox*)widget ;
        box->setChecked(arg1);
    }
}

void PlateLocator::on_moveButton_clicked()
{
    int count = ui->resList->count();
    int i = 0;
    while(i < count)
    {
        QListWidgetItem *item = ui->resList->item(i);
        QWidget *widget = ui->resList->itemWidget(item);
        QCheckBox *box = (QCheckBox*)widget ;
        if(box->isChecked())
        {
            QString classPath = savePath + "/plates/" + ui->showClass->currentText();
            QString filename = classPath + "/" + item->whatsThis();
            QString aimPath = savePath + "/plates/" + ui->aimClass->currentText() + "/" + item->whatsThis();
            QFile::copy(filename,aimPath);
            QDir classdir = QDir(classPath);
            classdir.remove(filename);
            delete item;
            count--;
        }else
        {
            i++;
        }
    }
}

void PlateLocator::on_autoClassify_clicked()
{
    QString XMLPath = QFileDialog::getOpenFileName(this, "选择XML文件路径", "E:/", "*.xml");
    if (XMLPath.isEmpty())
        return;
    PlateCategory_SVM::Load(XMLPath);
    QString classPath = savePath + "/plates/未识别";
    QDir* classdir = new QDir(classPath);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";
    QStringList sourcePlateNames = classdir->entryList(nameFilters);
    for (QString sourcePlateName : sourcePlateNames)
    {
        QString sourcePlatePath = classPath + "/" + sourcePlateName;
        std::string str = sourcePlatePath.toLocal8Bit().toStdString();
        cv::Mat sourcePlate = cv::imread(str);
        QString platecate = PlateCategoryString[PlateCategory_SVM::Test(sourcePlate)];
        QString aimPath = savePath + "/plates/" + platecate + "/" + sourcePlateName;
        QFile::copy(sourcePlatePath,aimPath);
        classdir->remove(sourcePlatePath);
    }
    ui->fileList->setCurrentRow(0);
    showSourcePlate();
}

void PlateLocator::on_centralTab_tabBarClicked(int index)
{
    if (imgSaved)
        showSourcePlate();
}

void PlateLocator::on_simpleXML_clicked()
{
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";

    QString notpath = savePath + "/plates/非车牌";
    QDir* dir = new QDir(notpath);
    QStringList notimgFileNames = dir->entryList(nameFilters);
    QString genpath = savePath + "/plates/普通车牌";
    dir = new QDir(genpath);
    QStringList genimgFileNames = dir->entryList(nameFilters);
    int imgcount = notimgFileNames.size() + genimgFileNames.size();

    cv::Mat mat;
    std::vector<float> descriptor;
    cv::Mat descriptorMat = cv::Mat::zeros(imgcount, 1188, CV_32FC1);
    int *label = (int *)malloc(sizeof(int)*imgcount);

    int i = 0;
    for (QString imgFileName : notimgFileNames)
    {
        QString filePath = notpath + "/" + imgFileName;
        std::string str = filePath.toLocal8Bit().toStdString();
        mat = cv::imread(str, cv::ImreadModes::IMREAD_GRAYSCALE);
        descriptor = PlateCategory_SVM::ComputeHogDescriptors(mat);
        for(int j = 0; j < 1188; j++)
        {
            descriptorMat.at<float>(i, j) = descriptor.at(j);
        }
        label[i] = 0;
        i++;
    }
    for (QString imgFileName : genimgFileNames)
    {
        QString filePath = genpath + "/" + imgFileName;
        std::string str = filePath.toLocal8Bit().toStdString();
        mat = cv::imread(str, cv::ImreadModes::IMREAD_GRAYSCALE);

        descriptor = PlateCategory_SVM::ComputeHogDescriptors(mat);
        for(int j = 0; j < 1188; j++)
        {
            descriptorMat.at<float>(i, j) = descriptor.at(j);
        }
        label[i] = 1;
        i++;
    }
    cv::Mat labelMat = cv::Mat(imgcount, 1, CV_32SC1, label);
    PlateCategory_SVM::Train(descriptorMat, labelMat);

    QString xmlSavePath = QFileDialog::getSaveFileName(this,"请选择XML保存路径","E:/简单XML.xml","*.xml");
    PlateCategory_SVM::Save(xmlSavePath);

    PlateCategory_SVM::Load(xmlSavePath);
    QString classPath = savePath + "/plates/未识别";
    QDir* classdir = new QDir(classPath);
    QStringList sourcePlateNames = classdir->entryList(nameFilters);
    for (QString sourcePlateName : sourcePlateNames)
    {
        QString sourcePlatePath = classPath + "/" + sourcePlateName;
        std::string str = sourcePlatePath.toLocal8Bit().toStdString();
        cv::Mat sourcePlate = cv::imread(str);
        QString platecate = PlateCategoryString[PlateCategory_SVM::Test(sourcePlate)];
        QString aimPath = savePath + "/plates/" + platecate + "/" + sourcePlateName;
        QFile::copy(sourcePlatePath,aimPath);
        classdir->remove(sourcePlatePath);
    }
    ui->fileList->setCurrentRow(0);
    showSourcePlate();
}

void PlateLocator::on_selectsourceplateButton_clicked()
{
    platesPath = QFileDialog::getExistingDirectory(this, "选择图片所在文件夹", "E:/");
    if (platesPath.isEmpty())
        return;
    QString genplatesPath = platesPath + "/plates/普通车牌";
    ui->plateList->clear();
    QDir* platesdir = new QDir(genplatesPath);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";
    sourcePlateNames = platesdir->entryList(nameFilters);
    for (QString sourcePlateName : sourcePlateNames)
    {
        ui->plateList->addItem(sourcePlateName);
    }
    ui->plateList->setCurrentRow(0);

}
