/*
 * This file is part of the OpenRPT report writer and rendering engine,
 * and is Copyright (c) 2001-2019 by OpenMFG LLC, d/b/a xTuple.  It
 * is licensed to you under the xTuple End-User License Agreement ("the
 * EULA"), the full text of which is available at www.xtuple.com/EULA.
 * While the EULA gives you access to source code and encourages your
 * involvement in the development process, this Package is not free
 * software.  By using this software, you agree to be bound by the
 * terms of the EULA.
 */

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
