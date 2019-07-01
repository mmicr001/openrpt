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

TEMPLATE = lib
CONFIG  += qt warn_on
DEFINES += MAKELIB

DESTDIR = ../../lib
MOC_DIR = tmp
OBJECTS_DIR = tmp
UI_DIR = tmp

INCLUDEPATH += ../common ../../common ../qzint

QMAKE_LIBDIR = ../../lib $$QMAKE_LIBDIR
LIBS += -lopenrptcommon -lMetaSQL -lqzint

HEADERS = openreports.h \
          barcodes.h \
          crosstab.h \
          graph.h \
          orcrosstab.h \
          orutils.h \
          orprerender.h \
          orprintrender.h \
          renderobjects.h \
          previewdialog.h \
          labelpaintengine.h \
          labelprintengine.h \
          satopaintengine.h \
          satoprintengine.h \
          zebrapaintengine.h \
          zebraprintengine.h \
          reportprinter.h \
          textelementsplitter.h \
          ../common/builtinformatfunctions.h \
          ../common/builtinSqlFunctions.h \
          ../common/labelsizeinfo.h \
          ../common/pagesizeinfo.h

SOURCES = openreports.cpp \
          3of9.cpp \
          ext3of9.cpp \
          i2of5.cpp \
          code128.cpp \
          codeean.cpp \
          crosstab.cpp \
          dmatrixbc.cpp \
          graph.cpp \
          orutils.cpp \
          orprerender.cpp \
          orprintrender.cpp \
          renderobjects.cpp \
          previewdialog.cpp \ 
          labelpaintengine.cpp \
          labelprintengine.cpp \
          satopaintengine.cpp \
          satoprintengine.cpp \
          zebrapaintengine.cpp \
          zebraprintengine.cpp \
          reportprinter.cpp \
          textelementsplitter.cpp \
          ../common/builtinformatfunctions.cpp \
          ../common/builtinSqlFunctions.cpp \
          ../common/labelsizeinfo.cpp \
          ../common/pagesizeinfo.cpp \ 
          pdf417bc.cpp \
          qrbc.cpp

QT += xml sql gui network printsupport core
