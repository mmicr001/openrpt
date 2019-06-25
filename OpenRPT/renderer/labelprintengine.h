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

#ifndef LABELPRINTENGINE_H
#define LABELPRINTENGINE_H

#include <QPrintEngine>

class LabelPaintEngine;
class ReportPrinter;

class LabelPrintEngine : public QPrintEngine
{
public:
  LabelPrintEngine(LabelPaintEngine *paintEngine, ReportPrinter *printer, int resolution);

  virtual bool	abort () { return true; }
  virtual int	metric ( QPaintDevice::PaintDeviceMetric id ) const;
  virtual bool	newPage ();
  virtual QPrinter::PrinterState	printerState () const;
  virtual QVariant	property ( PrintEnginePropertyKey key ) const;
  virtual void	setProperty ( PrintEnginePropertyKey key, const QVariant & value );

private:
  LabelPaintEngine *m_paintEngine;
  ReportPrinter   *m_printer;
  QString       m_printerName;
  QString       m_docName;
  QSizeF        m_paperSize;
  QRect         m_paperRect;
  int           m_resolution;
};

#endif // LABELPRINTENGINE_H
