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

#include "datamatrixconfig.h"
#include "ui_datamatrixconfig.h"

#include <QDebug>
DataMatrixConfig::DataMatrixConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataMatrixConfig)
{
    ui->setupUi(this);
}

DataMatrixConfig::~DataMatrixConfig()
{
    delete ui;
}

QString DataMatrixConfig::format(const QString &align) {
  QString format = QString("{"
                           "\"size\": %1,"
                           "\"alignment\": \"%2\","
                           "\"barcode\": \"DATAMATRIX\""
                           "}"
                           ).arg(ui->_size->currentIndex()).arg(align);
  return format;
}
