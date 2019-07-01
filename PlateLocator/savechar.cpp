#include "savechar.h"
#include "ui_savechar.h"

SaveChar::SaveChar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveChar)
{
    ui->setupUi(this);
    this->setWindowTitle("Saving");
    ui->OKButton->setEnabled(false);
    saveCharThread = new SaveCharThread();
    connect(saveCharThread,&SaveCharThread::progress,this,&SaveChar::updateProgress);
    connect(saveCharThread,&SaveCharThread::finished,this,&SaveChar::threadFinished);
}

SaveChar::~SaveChar()
{
    delete ui;
}

void SaveChar::updateProgress(int present)
{
    ui->progressBar->setValue(present);
}

void SaveChar::threadFinished()
{
    ui->progressBar->setValue(1000);
    ui->OKButton->setEnabled(true);
}

void SaveChar::init(QStringList sourcePlateNamesp, QString platesPathp, QString charsPathp, float gammaFactorp, int leftLimitp, int rightLimitp, int topLimitp, int bottomLimitp, int charminWidthp, int charmaxWidthp, int charminHeightp, int charmaxHeightp, float charminRatiop, float charmaxRatiop)
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

    saveCharThread->init(sourcePlateNames,platesPath,charsPath,gammaFactor,
                         leftLimit,rightLimit,topLimit,bottomLimit,
                         charminWidth,charmaxWidth,charminHeight,charmaxHeight,
                         charminRatio,charmaxRatio);
    saveCharThread->start();
}

void SaveChar::on_OKButton_clicked()
{
    this->destroy();
}

void SaveChar::on_CancelButton_clicked()
{
    saveCharThread->terminate();
    ui->OKButton->setEnabled(true);
    this->destroy();
}
