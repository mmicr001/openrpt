/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2018 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
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
