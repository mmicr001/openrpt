#include "qrconfig.h"
#include "ui_qrconfig.h"

#include <QDebug>
#include <QCheckBox>
QRConfig::QRConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QRConfig)
{
    ui->setupUi(this);
}

QRConfig::~QRConfig()
{
    delete ui;
}

void QRConfig::setAutoSize(const bool &p) {
    ui->_autosize->setChecked(p);
}

void QRConfig::setQRSize(const int &p) {
    ui->_qrSize->setCurrentIndex(p-1);
    ui->_qrsizeRad->setChecked(true);
}

void QRConfig::setErrorCorrection(const int &p) {
    if (p >= 0) {
        ui->_errorCorrection->setCurrentIndex(p-1);
        ui->_errorCorrectionChk->setChecked(true);
    }
}

QString QRConfig::format(const QString &align) {
    QString format = QString("{"
                             "\"size\": %1,"
                             "\"autosize\": \"%2\","
                             "\"errorCorrection\": %3,"
                             "\"alignment\": \"%4\","
                             "\"barcode\": \"QR\""
                             "}"
                             ).arg(ui->_qrSize->currentIndex()+1)
                              .arg(ui->_autosize->isChecked() ? "true" : "false")
                              .arg(ui->_errorCorrectionChk->isChecked() ? ui->_errorCorrection->currentIndex() + 1 : -1)
                              .arg(align);
    return format;
}
