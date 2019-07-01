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

#ifndef SATOPRINTENGINE_H
#define SATOPRINTENGINE_H

#include "labelprintengine.h"

class LabelPaintEngine;
class ReportPrinter;

class SatoPrintEngine : public LabelPrintEngine
{
public:
  SatoPrintEngine(LabelPaintEngine *paintEngine, ReportPrinter *printer);
};

#endif // SATOPRINTENGINE_H
