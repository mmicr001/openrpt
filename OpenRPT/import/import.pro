#
# This file is part of the OpenRPT report writer and rendering engine,
# and is Copyright (c) 2001-2019 by OpenMFG LLC, d/b/a xTuple.  It
# is licensed to you under the xTuple End-User License Agreement ("the
# EULA"), the full text of which is available at www.xtuple.com/EULA.
# While the EULA gives you access to source code and encourages your
# involvement in the development process, this Package is not free
# software.  By using this software, you agree to be bound by the
# terms of the EULA.
#

include( ../../global.pri )

TEMPLATE = app
TARGET = importrpt

CONFIG += warn_on console
CONFIG -= staticlib

QT += xml sql

DESTDIR     = ../../bin
MOC_DIR     = tmp
OBJECTS_DIR = tmp
UI_DIR      = tmp

INCLUDEPATH += ../../common ../common
QMAKE_LIBDIR = ../../lib $$QMAKE_LIBDIR
LIBS        += -lopenrptcommon

win32-msvc* {
  PRE_TARGETDEPS += ../../lib/openrptcommon.$${LIBEXT}
} else {
  PRE_TARGETDEPS += ../../lib/libopenrptcommon.$${LIBEXT}
}

macx:RC_FILE = ../images/OpenRPT-tools.icns

HEADERS += ../common/builtinSqlFunctions.h

SOURCES += main.cpp ../common/builtinSqlFunctions.cpp
