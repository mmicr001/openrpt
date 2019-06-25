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
#ifndef __ORPRINTRENDER_H__
#define __ORPRINTRENDER_H__

#include <QPrinter>
#include <QPainter>

class ORODocument;
class ReportPrinter;

class ORPrintRender
{
  public:
    ORPrintRender();
    virtual ~ORPrintRender();

    void setPrinter(QPrinter *);
    QPrinter * printer() { return _printer; }

    void setPainter(QPainter *);
    QPainter * painter() { return _painter; }

    bool setupPrinter(ORODocument *, QPrinter *);
    bool render(ORODocument *, ReportPrinter *);
    bool render(ORODocument *);

    static void renderPage(ORODocument * pDocument, int pageNb, QPainter *painter, qreal xDpi, qreal yDpi, QSize margins, int printResolution);
    static bool exportToPDF(ORODocument * pDocument, QString pdfFileName);

  protected:
    QPrinter* _printer;
    QPainter* _painter;
};

#endif // __ORPRINTRENDER_H__



