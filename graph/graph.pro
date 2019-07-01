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

include( ../global.pri )

TEMPLATE = app

CONFIG += qt warn_on
CONFIG -= staticlib

QT +=  sql widgets

DESTDIR     = ../bin
MOC_DIR     = tmp
OBJECTS_DIR = tmp
UI_DIR      = tmp

INCLUDEPATH += .

macx:RC_FILE = ../OpenRPT/images/OpenRPT-tools.icns
HEADERS += graph.h graphwindow.h
FORMS   += graphwindow.ui
SOURCES += graph.cpp graphwindow.cpp main.cpp
