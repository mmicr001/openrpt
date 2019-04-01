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
translations.extra = cd share/dict && $$dirname(QMAKE_QMAKE)/lrelease openrpt*.ts
msvc{
  translations.extra =  for %i IN ($${TRANSLATIONS}) DO $$dirname(QMAKE_QMAKE)/lrelease %i
}
