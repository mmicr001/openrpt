#
# OpenRPT report writer and rendering engine
# Copyright (C) 2001-2018 by OpenMFG, LLC
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
# Please contact info@openmfg.com with any questions on this license.
#

include( ../../global.pri )

TEMPLATE = app
TARGET   = RPTrender
unix:TARGET = rptrender

CONFIG  += qt warn_on

QT += xml sql network widgets printsupport

DESTDIR     = ../../bin
MOC_DIR     = tmp
OBJECTS_DIR = tmp
UI_DIR      = tmp

INCLUDEPATH += ../common ../../common ../../../openrpt-build-desktop/common ../renderer
QMAKE_LIBDIR = ../../lib $$QMAKE_LIBDIR
LIBS        += -lrenderer -lopenrptcommon -ldmtx -lMetaSQL -lqzint

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
