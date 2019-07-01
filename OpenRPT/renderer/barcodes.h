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

#ifndef __BARCODES_H__
#define __BARCODES_H__

#include <QRect>
#include <QString>
#include <QPainter>
class ORBarcodeData;
class OROBarcode;
class OROPage;

//
// 3of9
//
void render3of9(QPainter *, int, const QRectF &, const QString &, OROBarcode * bc);

//
// 3of9+
//
void renderExtended3of9(QPainter *, int, const QRectF &, const QString &, OROBarcode *bc);

//
// Interleaved 2 of 5
//
void renderI2of5(QPainter *, int, const QRectF &, const QString &, OROBarcode * bc);

//
// Code 128
//
void renderCode128(QPainter *, int, const QRectF &r, const QString &_str, OROBarcode *bc);

//
// Code EAN/UPC
//
void renderCodeEAN13(QPainter *, int, const QRectF &, const QString &, OROBarcode * bc);
void renderCodeEAN8(QPainter *, int, const QRectF &, const QString &, OROBarcode * bc);
void renderCodeUPCA(QPainter *, int, const QRectF &, const QString &, OROBarcode * bc);
void renderCodeUPCE(QPainter *, int, const QRectF &, const QString &, OROBarcode * bc);

//
// CodeDataMatrix
//
void renderDataMatrix(QPainter *, const QRectF &, const QString &, OROBarcode * bc);

//
// PDF417
//

void renderPDF417(QPainter *, int, const QRectF &, const QString &, OROBarcode * bc);

//
// QR
//

void renderQR(QPainter *, int, const QRectF &, const QString &, OROBarcode * bc);

typedef struct DmtxInfos_struct {
   int type;
   int xSize;
   int ySize;
   QString align;
} DmtxInfos;

DmtxInfos extractInfosDtmx(const QString &s);
#endif

