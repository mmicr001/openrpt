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

include( ../global.pri )

TEMPLATE    = lib
CONFIG      += qt warn_on
QT          += xml sql widgets
DEFINES     += MAKELIB

TARGET = openrptcommon

INCLUDEPATH = . ../OpenRPT/common

DESTDIR = ../lib
OBJECTS_DIR = tmp
MOC_DIR     = tmp
UI_DIR      = tmp

SOURCES = data.cpp \
          parameter.cpp \
          dbtools.cpp \
          xsqlquery.cpp \
          quuencode.cpp \
          login.cpp \
          loginOptions.cpp \
          xvariant.cpp \
          languageoptions.cpp \
          parameterproperties.cpp \
          paramlistedit.cpp \
          parameteredit.cpp \
          reportpageoptions.cpp \
          memdbloader.cpp \
          finddialog.cpp \
          ../OpenRPT/common/builtinSqlFunctions.cpp \
          ../OpenRPT/common/querysource.cpp \
          ../OpenRPT/common/parsexmlutils.cpp \

          
HEADERS = data.h \
          parameter.h \
          dbtools.h \
          xsqlquery.h \
          quuencode.h \
          login.h \
          loginOptions.h \
          xvariant.h \
          languageoptions.h \
          parameterproperties.h \
          paramlistedit.h \
          parameteredit.h \
          reportpageoptions.h \
          memdbloader.h \
          finddialog.h \
          ../OpenRPT/common/builtinSqlFunctions.h \
          ../OpenRPT/common/querysource.h \
          ../OpenRPT/common/parsexmlutils.h \

          
FORMS   =  parameterproperties.ui \
           paramlistedit.ui \
           login.ui \
           loginOptions.ui \
           parameteredit.ui \
           finddialog.ui \

RESOURCES += ../OpenRPT/images/OpenRPTCommon.qrc
