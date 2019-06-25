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

#include "data.h"

#include <QObject>

QString OpenRPT::build     = QObject::tr("%1 %2").arg(__DATE__, __TIME__);
QString OpenRPT::copyright = QObject::tr("Copyright (c) 2002-2019, OpenMFG, LLC.");
bool    OpenRPT::loggedIn  = false;
QString OpenRPT::version   = QObject::tr("3.4.0");

LanguageOptions OpenRPT::languages(0);

/* set the values for these in each main() or
   in the constructor for the primary UI of embedded components:
 */
QString OpenRPT::databaseURL = QString::null;
QString OpenRPT::name = QString::null;
