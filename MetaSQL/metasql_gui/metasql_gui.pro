#
# OpenRPT report writer and rendering engine
# Copyright (C) 2001-2019 by OpenMFG, LLC
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
TARGET   = metasql

CONFIG += qt warn_on
CONFIG -= staticlib
QT     +=  sql xml widgets  printsupport

DESTDIR     = ../../bin
MOC_DIR     = tmp
OBJECTS_DIR = tmp
UI_DIR      = tmp

INCLUDEPATH += .. ../tmp ../../common  ../../../openrpt-build-desktop/MetaSQL/tmp  ../../../openrpt-build-desktop/common
DEPENDPATH  += .. ../tmp ../../common  ../../../openrpt-build-desktop/MetaSQL/tmp  ../../../openrpt-build-desktop/common

QMAKE_LIBDIR = ../../lib $$QMAKE_LIBDIR
LIBS        += -lMetaSQL -lopenrptcommon

win32-msvc* {
  PRE_TARGETDEPS += ../../lib/MetaSQL.$${LIBEXT}
  PRE_TARGETDEPS += ../../lib/openrptcommon.$${LIBEXT}
} else {
  PRE_TARGETDEPS += ../../lib/libMetaSQL.$${LIBEXT}
  PRE_TARGETDEPS += ../../lib/libopenrptcommon.$${LIBEXT}
}

macx:RC_FILE = ../../OpenRPT/images/OpenRPT-tools.icns

SOURCES += main.cpp
