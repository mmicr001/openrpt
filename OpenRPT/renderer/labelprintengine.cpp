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

#include <QPrinter>
#include <QPrintEngine>
#include <QFile>
#include <QtDebug>
#include <QHostInfo>
#include <QTextCodec>
#include "labelprintengine.h"
#include "labelpaintengine.h"
#include "reportprinter.h"


LabelPrintEngine::LabelPrintEngine(LabelPaintEngine *paintEngine, ReportPrinter *printer, int resolution) : m_paintEngine(paintEngine), m_printer(printer), m_resolution(resolution)
{
  QString customResolution = printer->getParam("dpi");
  if(customResolution.toInt() > 0) {
    m_resolution = customResolution.toInt();
  }
}


QPrinter::PrinterState	LabelPrintEngine::printerState () const
{
  if(m_printer->paintingActive()) {
    return QPrinter::Active;
  }
  else {
    return QPrinter::Idle;
  }
}

int	LabelPrintEngine::metric ( QPaintDevice::PaintDeviceMetric id ) const
{
  int val = 1;

  switch (id) {
  case QPaintDevice::PdmWidth:
      break;
  case QPaintDevice::PdmHeight:
      break;
  case QPaintDevice::PdmDpiX:
  case QPaintDevice::PdmDpiY:
  case QPaintDevice::PdmPhysicalDpiX:
  case QPaintDevice::PdmPhysicalDpiY:
    val = m_resolution;
    break;

  case QPaintDevice::PdmWidthMM:
      break;
  case QPaintDevice::PdmHeightMM:
    break;
  case QPaintDevice::PdmNumColors:
    val = 2;
    break;
  case QPaintDevice::PdmDepth:
    val = 1;
    break;
  default:
      qWarning("QPrinter::metric: Invalid metric command");
      val = 0;
  }
  return val;
}

void	LabelPrintEngine::setProperty ( PrintEnginePropertyKey key, const QVariant & value )
{
  switch(key) {
  case  QPrintEngine::PPK_PrinterName:
    m_printerName = value.toString();
    break;
  case  QPrintEngine::PPK_DocumentName:
    m_docName = value.toString();
    break;
  case  QPrintEngine::PPK_CustomPaperSize:
    m_paperSize = value.toSizeF();
    m_paperRect = QRect(QPoint(0,0),m_paperSize.toSize());
    break;
  case  QPrintEngine::PPK_PaperRect:
  case  QPrintEngine::PPK_PageRect:
    m_paperSize = value.toRect().size();
    m_paperRect = value.toRect();
    break;
  case  QPrintEngine::PPK_PageSize:
    // not implemented
    break;
  case  QPrintEngine::PPK_Resolution:
    m_resolution = value.toInt();
    break;
  default: break;
  }
}

QVariant	LabelPrintEngine::property ( PrintEnginePropertyKey key ) const
{
  switch(key) {
  case  QPrintEngine::PPK_PrinterName:
    return QVariant(m_printerName);

  case  QPrintEngine::PPK_DocumentName:
    return QVariant(m_docName);

  case  QPrintEngine::PPK_PaperRect:
  case  QPrintEngine::PPK_PageRect:
    return QVariant(m_paperRect);

  case  QPrintEngine::PPK_CustomPaperSize:
    return QVariant(m_paperSize);

  case  QPrintEngine::PPK_Resolution:
    return QVariant(m_resolution);

  // case  QPrintEngine::PPK_CopyCount:
  case  QPrintEngine::PPK_NumberOfCopies:
    return QVariant(1);

  default: return QVariant();
  }
}

bool	LabelPrintEngine::newPage ()
{
  return m_paintEngine->newPage();
}

