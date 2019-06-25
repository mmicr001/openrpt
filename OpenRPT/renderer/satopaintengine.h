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

#ifndef SATOPAINTENGINE_H
#define SATOPAINTENGINE_H

#include "labelpaintengine.h"
#include "reportprinter.h"

class SatoPaintEngine : public LabelPaintEngine
{
public:
  SatoPaintEngine(ReportPrinter *parentPrinter);

  virtual bool 	begin ( QPaintDevice * pdev );

  virtual void 	drawImage ( const QRectF & rectangle, const QImage & image, const QRectF & sr, Qt::ImageConversionFlags flags = Qt::AutoColor );
  virtual void 	drawLines ( const QLineF * lines, int lineCount );
  virtual void 	drawRects ( const QRectF * rects, int rectCount );

  virtual void 	addEndMessage ();


protected:
  virtual void  drawBarcode ( const QPointF & p, const QString &format, int height, int width, int narrowBar, QString barcodeData );
  virtual void  drawText ( const QPointF &p, const QString & text, const QFont &font = QFont());
  virtual QString rotation0Cmd() const { return "%0"; }
  virtual QString rotation90Cmd() const { return "%3"; }
  virtual QString rotation180Cmd() const { return "%2"; }
  virtual QString rotation270Cmd() const { return "%1"; }


private:

  QList<QRect> m_ReverseZones;

};

#endif // SATOPAINTENGINE_H
