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
          parsexmlutils.cpp \
          querysource.cpp \
          reportpageoptions.cpp \
          memdbloader.cpp \
          finddialog.cpp \
          ../OpenRPT/common/builtinSqlFunctions.cpp

          
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
          parsexmlutils.h \
          querysource.h \
          reportpageoptions.h \
          memdbloader.h \
          finddialog.h \
          ../OpenRPT/common/builtinSqlFunctions.h

          
FORMS   =  parameterproperties.ui \
           paramlistedit.ui \
           login.ui \
           loginOptions.ui \
           parameteredit.ui \
           finddialog.ui \

RESOURCES += ../OpenRPT/images/OpenRPTCommon.qrc
