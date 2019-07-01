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

#include <QString>
#include <QRectF>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#if QT_VERSION >= 0x050000
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#endif
#include "parsexmlutils.h"
#include "renderobjects.h"
#include "barcodeitem.h"
#include "zint.h"

void renderPDF417(QPainter *painter, int /*dpi*/, const QRectF &r, const QString &_str, OROBarcode *bc)
{
  #if QT_VERSION >= 0x050000
  QByteArray ba = QByteArray(bc->format().toStdString().c_str(), bc->format().toStdString().length());
  QJsonDocument doc = QJsonDocument::fromJson(ba);
  QJsonObject obj = doc.object();
  QJsonValue codewords = obj.value("codewords");
  QJsonValue columns = obj.value("columns");
  QJsonValue errorCorrection = obj.value("errorCorrection");
  QJsonValue type = obj.value("type");

  QPen pen(Qt::NoPen);
  QBrush brush(QColor("black"));
  painter->save();
  painter->setPen(pen);
  painter->setBrush(brush);

  QString str = _str;
  BarcodeItem bci;
  bci.ar=(Zint::QZint::AspectRatioMode)0;
  bci.bc.setText(str);
  bci.bc.setSecurityLevel(errorCorrection.toInt());
  bci.bc.setWidth(columns.toInt());
  bci.bc.setInputMode(UNICODE_MODE);
  if (type.toString() == "truncated")
      bci.bc.setSymbol(BARCODE_PDF417TRUNC);
  else
      bci.bc.setSymbol(BARCODE_PDF417);
  bci.bc.setPdf417CodeWords(codewords.toInt());
  bci.bc.setWhitespace(0);
  bci.bc.setFgColor(QColor("black"));
  bci.bc.setBgColor(QColor("white"));
  bci.update();

  bci.paint(painter, r);
  bci.update();

  painter->restore();
  #endif
  return;
}
