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
TARGET   = importmqlgui

CONFIG += qt warn_on
CONFIG -= staticlib
INCLUDEPATH += ../../OpenRPT/common ../../common ../../../openrpt-build-desktop/common .. .

QT += xml sql widgets

DESTDIR     = ../../bin
MOC_DIR     = tmp
OBJECTS_DIR = tmp
UI_DIR      = tmp

INCLUDEPATH += ../../OpenRPT/common ../../common ../../../openrpt-build-desktop/common .. .

QMAKE_LIBDIR = ../../lib $$QMAKE_LIBDIR
LIBS        += -lMetaSQL -lopenrptcommon

macx:RC_FILE = ../../OpenRPT/images/OpenRPT-tools.icns

FORMS   += importwindow.ui

HEADERS += importwindow.h \
           ../../OpenRPT/common/builtinSqlFunctions.h

SOURCES += importwindow.cpp \
           ../../OpenRPT/common/builtinSqlFunctions.cpp \
           main.cpp
