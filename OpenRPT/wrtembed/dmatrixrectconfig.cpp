#include "dmatrixrectconfig.h"
#include "ui_dmatrixrectconfig.h"



DMatrixRectConfig::DMatrixRectConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DMatrixRectConfig)
{
    ui->setupUi(this);
    connect(this->ui->_CFormat, SIGNAL(currentIndexChanged(int)),   this,           SLOT(capacityRefresh(int)));
    connect(this->ui->_CFormat, SIGNAL(currentIndexChanged(int)),   this,           SLOT(indexType(int)));
}

DMatrixRectConfig::~DMatrixRectConfig()
{
    delete ui;
}
//format                                  8x18        8x32        12x26       12x36       16x36       16x48
QString DMatrixRectConfig::capacite[] = {   "10/6",     "20/13",    "32/22",    "44/31",    "64/46",    "98/72"};

QString DMatrixRectConfig::format()
{
    int type = 24 + this->ui->_CFormat->currentIndex();
    QString out = "datamatrix_";
    out.append(QString::number(type));
    return out;
}

void DMatrixRectConfig::capacityRefresh(int i)
{
    this->ui->_LCapacite->setText(DMatrixRectConfig::capacite[i]);
}

void DMatrixRectConfig::indexType(int index)
{
    emit this->signalType(index + 24);
}

void DMatrixRectConfig::setVisible2(bool visible)
{
    this->setVisible(visible);
}

void DMatrixRectConfig::setIndexValue(int index)
{
    this->ui->_CFormat->setCurrentIndex(index);
}
