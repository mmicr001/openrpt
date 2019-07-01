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
#include "renderobjects.h"
#include "barcodeitem.h"
#include "zint.h"
#include "barcodes.h"

DmtxInfos extractInfosDtmx(const QString &s)
{
  const int sizes[][2] = {
      {10,10},
      {12,12},
      {14,14},
      {16,16},
      {18,18},
      {20,20},
      {22,22},
      {24,24},
      {26,26},
      {32,32},
      {36,36},
      {40,40},
      {44,44},
      {48,48},
      {52,52},
      {64,64},
      {72,72},
      {80,80},
      {88,88},
      {96,96},
      {104,104},
      {120,120},
      {132,132},
      {144,144},
      {8,18},
      {18,32},
      {12,26},
      {12,36},
      {16,36},
      {16,48}
  };

  int nbNsizes = sizeof(sizes)/sizeof(sizes[0]);

  DmtxInfos res;

  QRegExp regex("[a-zA-Z]{10}_([0-9]{1,2})_([LCR]{1})");
  regex.indexIn(s);
  res.type = regex.cap(1).toInt();
  res.align = regex.cap(2);
  if(res.type>0 && res.type<nbNsizes ) {
    res.ySize = sizes[res.type][0];
    res.xSize = sizes[res.type][1];
  }
  else {
    res.xSize = res.ySize = 1;
  }

  return res;
}

void renderDataMatrix(QPainter *painter, const QRectF &r, const QString &_str, OROBarcode *bc)
{
  QRegExp regex("[a-zA-Z]{10}_([0-9]{1,2})_([LCR]{1})");
  regex.indexIn(bc->format());
  int type = regex.cap(1).toInt();

  QPen pen(Qt::NoPen);
  QBrush brush(QColor("black"));
  painter->save();
  painter->setPen(pen);
  painter->setBrush(brush);

  BarcodeItem bci;
  bci.ar=(Zint::QZint::AspectRatioMode)1;
  bci.bc.setText(_str);
  bci.bc.setSecurityLevel(1);
  bci.bc.setInputMode(UNICODE_MODE);
  bci.bc.setSymbol(BARCODE_DATAMATRIX);
  bci.bc.setOption3(0);
  bci.bc.setWidth(type);
  bci.bc.setFgColor(QColor("black"));
  bci.bc.setBgColor(QColor("white"));
  bci.bc.setBorderType((Zint::QZint::BorderType)0);
  bci.bc.setBorderWidth(0);
  bci.bc.setWhitespace(0);
  bci.update();

  bci.paint(painter, r);
  bci.update();

  painter->restore();
  return;
}
