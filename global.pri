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

#
# This file is included by all the other project files
# and is where options or configurations that affect all
# of the projects can be place.
#

CONFIG += release dll c++11
# TEMPORARY HACK
win32 {
  CONFIG -= dll
  CONFIG += staticlib
}
macx {
  CONFIG -= dll
  CONFIG += staticlib
}

# NO_PNG removes dependency on libpng for Zint
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0 NO_PNG

LIBEXT = $${QMAKE_EXTENSION_SHLIB}
win32-g++:LIBEXT = a
win32-msvc*:LIBEXT = lib
macx:LIBEXT      = a
isEmpty( LIBEXT ) {
  win32:LIBEXT	= a
  unix:LIBEXT  = so
}

macx:exists(macx.pri) {
  include(macx.pri)
}

win32:exists(win32.pri) {
  include(win32.pri)
}

unix:exists(unix.pri) {
  include(unix.pri)
}
