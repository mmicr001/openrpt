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
CONFIG += qt warn_on
CONFIG -= staticlib
INCLUDEPATH += ../common ../../common ../../../openrpt-build-desktop/common ../renderer

win*:TARGET  = RPTrender
unix:TARGET = rptrender

CONFIG  += qt warn_on

QT += xml sql network widgets printsupport

DESTDIR     = ../../bin
MOC_DIR     = tmp
OBJECTS_DIR = tmp
UI_DIR      = tmp

INCLUDEPATH += ../common ../../common ../../../openrpt-build-desktop/common ../renderer
QMAKE_LIBDIR = ../../lib $$QMAKE_LIBDIR
LIBS        += -lrenderer -lopenrptcommon -lMetaSQL -lqzint

win32-msvc* {
  PRE_TARGETDEPS += ../../lib/renderer.$${LIBEXT} \
                    ../../lib/openrptcommon.$${LIBEXT}
} else {
  PRE_TARGETDEPS += ../../lib/librenderer.$${LIBEXT} \
                    ../../lib/libopenrptcommon.$${LIBEXT}
}

RC_FILE = renderapp.rc
macx:RC_FILE = ../images/OpenRPT-print.icns

# Input
FORMS   += renderwindow.ui \
           ../wrtembed/dbfiledialog.ui

HEADERS += ../wrtembed/dbfiledialog.h \
           renderwindow.h

SOURCES += ../wrtembed/dbfiledialog.cpp \
           renderwindow.cpp \
           main.cpp
