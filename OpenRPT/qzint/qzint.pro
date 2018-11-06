include( ../../global.pri )

QT       += core gui uitools widgets

LIBS += -lz -lfontconfig

TARGET = qzint
TEMPLATE = lib
DEFINES += MAKELIB
DESTDIR = ../../lib

HEADERS +=  barcodeitem.h \
            aztec.h \
            bmp.h \
            code49.h \
            common.h \
            composite.h \
            dmatrix.h \
            eci.h \
            font.h \
            gridmtx.h \
            gs1.h \
            hanxin.h \
            large.h \
            maxicode.h \
            pcx.h \
            pdf417.h \
            reedsol.h \
            rss.h \
            sjis.h \
            stdint_msvc.h \
            zint.h \
            qzint.h

SOURCES += barcodeitem.cpp \
           2of5.c \
           auspost.c \
           aztec.c \
           bmp.c \
           codablock.c \
           code.c \
           code128.c \
           code16k.c \
           code49.c \
           common.c \
           composite.c \
           dmatrix.c \
           dotcode.c \
           eci.c \
           emf.c \
           gif.c \
           gridmtx.c \
           gs1.c \
           hanxin.c \
           imail.c \
           large.c \
           library.c \
           mailmark.c \
           maxicode.c \
           medical.c \
           pcx.c \
           pdf417.c \
           plessey.c \
           postal.c \
           ps.c \
           raster.c \
           reedsol.c \
           render.c \
           rss.c \
           svg.c \
           telepen.c \
           tif.c \
           upcean.c \
           qr.c \
           dllversion.c \
           code1.c \
           png.c \
           qzint.cpp
