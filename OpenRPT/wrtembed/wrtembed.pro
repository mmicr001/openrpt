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

INCLUDEPATH = ../../common ../common ../../../openrpt-build-desktop/common ../renderer ../images ../../MetaSQL .

DESTDIR = ../../lib
MOC_DIR = tmp
UI_DIR = tmp
OBJECTS_DIR = tmp
QT += xml sql widgets printsupport

QMAKE_LIBDIR = ../../lib $$QMAKE_LIBDIR
LIBS += -lopenrptcommon -lrenderer -lqzint

FORMS   += datamatrixconfig.ui \
           labeleditor.ui \
           labeldefinitions.ui \
           labeldefinitioneditor.ui \
           queryeditor.ui \
           querylist.ui \
           pagesetup.ui \
           sectioneditor.ui \
           detailsectiondialog.ui \
           fieldeditor.ui \
           texteditor.ui \
           barcodeeditor.ui \
           reportproperties.ui \
           reportparameter.ui \
           reportparameterlist.ui \
           reportparameterlistitem.ui \
           imageeditor.ui \
           coloreditor.ui \
           colorlist.ui \
           grapheditor.ui \
           detailgroupsectiondialog.ui \
           editpreferences.ui \
           dbfiledialog.ui \
           crosstabeditor.ui \
           dmatrixsquareconfig.ui \
           dmatrixrectconfig.ui \
           dbarcodeconfig.ui \
           dmatrixpreview.ui \
           patheditor.ui \
           pdf417config.ui \
           qrconfig.ui

HEADERS += reportgridoptions.h\
           reporthandler.h \
           datamatrixconfig.h \
           documentwindow.h \
           documentview.h \
           documentscene.h \
           graphicsitems.h \
           graphicssection.h \
           labeleditor.h \
           labeldefinitions.h \
           labeldefinitioneditor.h \
           queryeditor.h \
           querylist.h \
           pagesetup.h \
           sectioneditor.h \
           detailsectiondialog.h \
           fieldeditor.h \
           texteditor.h \
           barcodeeditor.h \
           reportproperties.h \
           reportparameter.h \
           reportparameterlist.h \
           reportparameterlistitem.h \
           imageeditor.h \
           coloreditor.h \
           colorlist.h \
           grapheditor.h \
           detailgroupsectiondialog.h \
           editpreferences.h \
           dbfiledialog.h \
           crosstabeditor.h \
		   buddycombobox.h \
           querycombobox.h \
           fontutils.h \
           dmatrixsquareconfig.h \
           dmatrixrectconfig.h \
           dbarcodeconfig.h \
           patheditor.h \
           pdf417config.h \
           qrconfig.h

SOURCES += reportgridoptions.cpp\
           reporthandler.cpp \
           datamatrixconfig.cpp \
           documentwindow.cpp \
           documentview.cpp \
           documentscene.cpp \
           graphicsitems.cpp \
           graphicssection.cpp \
           labeldefinitions.cpp \
           labeldefinitioneditor.cpp \
           labeleditor.cpp \
           queryeditor.cpp \
           querylist.cpp \
           pagesetup.cpp \
           sectioneditor.cpp \
           detailsectiondialog.cpp \
           fieldeditor.cpp \
           texteditor.cpp \
           barcodeeditor.cpp \
           reportproperties.cpp \
           reportparameter.cpp \
           reportparameterlist.cpp \
           reportparameterlistitem.cpp \
           imageeditor.cpp \
           coloreditor.cpp \
           colorlist.cpp \
           grapheditor.cpp \
           detailgroupsectiondialog.cpp \
           editpreferences.cpp \
           dbfiledialog.cpp \
           crosstabeditor.cpp \
		   buddycombobox.cpp \
           querycombobox.cpp \
           fontutils.cpp \
           dmatrixsquareconfig.cpp \
           dmatrixrectconfig.cpp \
           dbarcodeconfig.cpp \
           patheditor.cpp \
           pdf417config.cpp \
           qrconfig.cpp


RESOURCES += ../images/OpenRPTWrtembed.qrc
