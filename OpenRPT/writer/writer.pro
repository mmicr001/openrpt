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
TARGET   = OpenRPT
unix:TARGET = openrpt

CONFIG += qt warn_on

QT += xml sql network widgets printsupport

DESTDIR     = ../../bin
MOC_DIR     = tmp
OBJECTS_DIR = tmp
UI_DIR      = tmp

INCLUDEPATH += ../../common ../common ../images
QMAKE_LIBDIR = ../../lib $$QMAKE_LIBDIR
LIBS        += -lwrtembed -lopenrptcommon -lrenderer -ldmtx -lMetaSQL -lqzint

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
