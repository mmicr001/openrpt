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

#include "reportprinter.h"
#include "labelpaintengine.h"
#include "satopaintengine.h"
#include "satoprintengine.h"
#include "zebrapaintengine.h"
#include "zebraprintengine.h"


static QString getParamValue(QString key, QList<QPair<QString,QString> > list)
{
  for(QList<QPair<QString,QString> >::iterator it = list.begin(); it != list.end(); it++) {
     if((*it).first == key) {
      return (*it).second;
    }
  }
  return "";
}

QString ReportPrinter::getRecallMask(QList<QPair<QString,QString> > params)
{
  QString id = getParamValue("recall", params);
  return id;
}

QString ReportPrinter::getStoreMask (QList<QPair<QString,QString> > params)
{
  QString id = getParamValue("store", params);
  return id;
}

QString ReportPrinter::getParam(QString key) const
{
  return getParamValue(key, _params);
}


ReportPrinter::ReportPrinter(PrinterMode mode, ReportPrinter::type type) : QPrinter(mode), m_paintEngine(NULL), m_printEngine(NULL), m_printerType(Standard), m_printToBuffer(false)
{
  setPrinterType(type);
}

ReportPrinter::~ReportPrinter()
{
  releaseEngines();
}

bool ReportPrinter::isLabelPrinter() const
{
  return m_printerType!=Standard;
}

void ReportPrinter::releaseEngines()
{
  if (m_paintEngine) delete m_paintEngine;
  if (m_printEngine) delete m_printEngine;
  m_paintEngine = 0;
  m_printEngine = 0;
}

void ReportPrinter::setPrintToBuffer() {
    m_printToBuffer = true;
	if (m_paintEngine != 0)
        m_paintEngine->setPrintToBuffer();
}

void ReportPrinter::setPrinterType(type type)
{
  if(outputFormat() != QPrinter::NativeFormat) {
    type = Standard;
  }

  if(type == m_printerType) {
    return;
  }

  // NB engines switch resets printer properties, we have to save them
  // (and also note that the print dialog can't support and custom printers, so it has to be called before switching to a custom type)
  QString savePrinterName = printerName();

  releaseEngines();

  switch (type) {
  case Sato:
    m_paintEngine = new SatoPaintEngine(this);
    if (m_printToBuffer)
      m_paintEngine->setPrintToBuffer();

    m_printEngine = new SatoPrintEngine(m_paintEngine, this);
    break;

  case Zebra:
    m_paintEngine = new ZebraPaintEngine(this);
    if (m_printToBuffer)
      m_paintEngine->setPrintToBuffer();

    m_printEngine = new ZebraPrintEngine(m_paintEngine, this);
    break;

  default:
    break;
  }

  if(m_paintEngine && m_printEngine) {
    setEngines(m_printEngine, m_paintEngine);
  }
  m_printerType = type;
  setPrinterName(savePrinterName);
}


QByteArray ReportPrinter::getBuffer() const {
	if (m_paintEngine == 0)
		return QByteArray();
	return m_paintEngine->getBuffer();
}

