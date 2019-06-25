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

TEMPLATE = lib

CONFIG  += qt warn_on

QT      +=  sql xml widgets printsupport

DEFINES += MAKELIB

DESTDIR     = ../lib
UI_DIR      = tmp
MOC_DIR     = tmp
OBJECTS_DIR = tmp

INCLUDEPATH += ../common  ../../openrpt-build-desktop/common
DEPENDPATH  += ../common  ../../openrpt-build-desktop/common

QMAKE_LIBDIR += ../lib
LIBS         += -lopenrptcommon

# override CONFIG warn_on for C files but not C++
macx:      QMAKE_CFLAGS_WARN_ON  = -Wno-missing-braces
win32-g++: QMAKE_CFLAGS_WARN_ON  = -Wno-missing-braces
unix:      QMAKE_CFLAGS_WARN_ON  = -Wno-missing-braces

FORMS   += logoutput.ui \
           metasqlsaveparameters.ui \
           mqledit.ui \
           resultsoutput.ui \
           selectmql.ui \

HEADERS += logoutput.h \
           metasql.h \
           metasqlqueryparser.h \
           metasqlhighlighter.h \
           metasqlsaveparameters.h \
           mqledit.h \
           mqlutil.h \
           resultsoutput.h \
           selectmql.h \

SOURCES += logoutput.cpp \
           metasql.cpp \
           metasqlqueryparser.cpp \
           metasqlhighlighter.cpp \
           metasqlsaveparameters.cpp \
           mqledit.cpp \
           mqlutil.cpp \
           resultsoutput.cpp \
           selectmql.cpp \

RESOURCES += ../OpenRPT/images/OpenRPTMetaSQL.qrc
