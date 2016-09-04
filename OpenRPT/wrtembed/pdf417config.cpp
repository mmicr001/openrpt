#include "pdf417config.h"
#include "ui_pdf417config.h"

#include <QDebug>
PDF417Config::PDF417Config(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PDF417Config)
{
    ui->setupUi(this);
}

PDF417Config::~PDF417Config()
{
    delete ui;
}

void PDF417Config::setCodewords(const int &p) {
    ui->_codewords->setValue(p);
}

void PDF417Config::setColumns(const int &p) {
    ui->_columns->setCurrentIndex(p);
}

void PDF417Config::setErrorCorrecton(const int &p) {
    ui->_errorCorrection->setCurrentIndex(p+1);
}

void PDF417Config ::setType(const BCType &type) {
    if (type == Truncated)
        ui->_truncated->setChecked(true);
    else
        ui->_standard->setChecked(true);
}

QString PDF417Config::format(const QString &align) {
  QString format = QString("{"
                           "\"codewords\": %1,"
                           "\"columns\": %2,"
                           "\"errorCorrection\": %3,"
                           "\"type\": \"%4\","
                           "\"alignment\": \"%5\","
                           "\"barcode\": \"PDF417\""
                           "}"
                           ).arg(ui->_codewords->value()).arg(ui->_columns->currentIndex())
                            .arg(ui->_errorCorrection->currentIndex()-1).arg(ui->_standard->isChecked() ? "standard" : "truncated")
                            .arg(align);
  return format;
}
