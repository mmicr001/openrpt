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

#ifndef REPORTPRINTER_H
#define REPORTPRINTER_H

#include <QPrinter>
#include <QPair>
#include <QList>


class LabelPaintEngine;

class ReportPrinter : public QPrinter
{
public:

  enum type {Standard, Sato, Zebra};
  enum barcode {Code3of9, Code128, EAN13, EAN8, UPCA, UPCE, DataMatrix};
  static const QString barcodePrefix() { return "<bc>"; }

  ReportPrinter(PrinterMode mode = ScreenResolution, ReportPrinter::type type=Standard);
  ~ReportPrinter();

  bool isLabelPrinter() const;
  void setPrinterType(type type);
  void			setPrintToBuffer();
  QByteArray	getBuffer() const;
  void setParams(QList<QPair<QString,QString> > params) { _params = params; }
  QList<QPair<QString,QString> > getParams() const { return _params; }
  QString getParam(QString key) const;

  int printerMetric(QPaintDevice::PaintDeviceMetric id) const { return metric(id); }


  static   QString getRecallMask(QList<QPair<QString,QString> > params);
  static   QString getStoreMask(QList<QPair<QString,QString> > params);

private:
  LabelPaintEngine*     m_paintEngine;
  QPrintEngine*         m_printEngine;
  type                  m_printerType;
  bool					m_printToBuffer;
  QString				m_cmdPrefix;
  QList<QPair<QString,QString> >  _params;

  void releaseEngines();
};

#endif // REPORTPRINTER_H
