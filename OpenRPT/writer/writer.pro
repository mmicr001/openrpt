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
TARGET   = OpenRPT
unix:TARGET = openrpt

CONFIG += qt warn_on
CONFIG -= staticlib

QT += xml sql network widgets printsupport

DESTDIR     = ../../bin
MOC_DIR     = tmp
OBJECTS_DIR = tmp
UI_DIR      = tmp

INCLUDEPATH += ../../common ../common ../images
QMAKE_LIBDIR = ../../lib $$QMAKE_LIBDIR
LIBS        += -lwrtembed -lopenrptcommon -lrenderer -lMetaSQL -lqzint

win32-msvc* {
  PRE_TARGETDEPS += ../../lib/wrtembed.$${LIBEXT}       \
                    ../../lib/openrptcommon.$${LIBEXT}  \
                    ../../lib/renderer.$${LIBEXT}
} else {
  PRE_TARGETDEPS += ../../lib/libwrtembed.$${LIBEXT}            \
                    ../../lib/libopenrptcommon.$${LIBEXT}       \
                    ../../lib/librenderer.$${LIBEXT}
}

RC_FILE      = writer.rc
macx:RC_FILE = ../images/OpenRPT.icns
RESOURCES   += writer.qrc

HEADERS += reportwriterwindow.h \

SOURCES += rptwrt.cpp\
           reportwriterwindow.cpp
