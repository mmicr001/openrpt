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

include( global.pri )


TEMPLATE = subdirs
SUBDIRS = common \
          graph \
          MetaSQL \
          MetaSQL/metasql_gui \
          MetaSQL/importmql_gui \
          OpenRPT/qzint \
          OpenRPT/renderer \
          OpenRPT/wrtembed \
          OpenRPT/writer \
          OpenRPT/renderapp \
          OpenRPT/import \
          OpenRPT/import_gui \
          OpenRPT/export

CONFIG += ordered

TRANSLATIONS = dict/openrpt.ar.ts \
               dict/openrpt.base.ts \
               dict/openrpt.es.ts \
               dict/openrpt.fr.ts \
               dict/openrpt.it.ts \
               dict/openrpt.ru.ts

macx {
  QMAKE_INFO_PLIST = Info.plist
}

INSTALLS = translations

translations.path = bin/dict
translations.files = $$replace(TRANSLATIONS, ts, qm)
translations.extra = cd dict && $$dirname(QMAKE_QMAKE)/lrelease openrpt*.ts
msvc{
  translations.extra =  for %i IN ($${TRANSLATIONS}) DO $$dirname(QMAKE_QMAKE)/lrelease %i
}
