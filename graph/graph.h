/*
 * This file is part of the OpenRPT report writer and rendering engine,
 * and is Copyright (c) 2001-2019 by OpenMFG LLC, d/b/a xTuple.  It
 * is licensed to you under the xTuple End-User License Agreement ("the
 * EULA"), the full text of which is available at www.xtuple.com/EULA.
 * While the EULA gives you access to source code and encourages your
 * involvement in the development process, this Package is not free
 * software.  By using this software, you agree to be bound by the
 * terms of the EULA.
 */

#ifndef __GRAPH_WIDGET_H__
#define __GRAPH_WIDGET_H__

#include <qwidget.h>
#include <qstring.h>
#include <qmap.h>
#include <qpair.h>
#include <qsqlquery.h>
#include <qcolor.h>
#include <qfont.h>
//Added by qt3to4:
#include <QPaintEvent>

typedef QPair<int, double> TSetValue;
typedef QMap<int, double> GSetValue;
typedef QPair<QString, GSetValue> GReference;
typedef QMap<int, GReference> GReferences;


class Graph : public QWidget {
    Q_OBJECT
    public:
        Graph(QWidget* = 0, const char* = 0);
        ~Graph();

        int hPadding();
        int vPadding();

        QString dataLabel();
        QString valueLabel();
        QString title();

        QFont titleFont();
        QFont dataLabelFont();
        QFont dataFont();
        QFont valueLabelFont();
        QFont valueFont();

        int   titleAlignment();
        int   dataLabelAlignment();
        int   valueLabelAlignment();

        QColor getSetColor(int);

        double minValue();
        double maxValue();

        bool drawBars();
        bool drawLines();
        bool drawPoints();

        bool autoMinMax();
        bool autoRepaint();

        void populateFromResult(QSqlQuery&);

    public slots:
        void setHPadding(int);
        void setVPadding(int);

        void setDataLabel(const QString&);
        void setValueLabel(const QString&);
        void setTitle(const QString&);

        void setTitleFont(const QFont *);
        void setTitleFont(const QFont &);
        void setDataLabelFont(const QFont *);
        void setDataLabelFont(const QFont &);
        void setDataFont(const QFont *);
        void setDataFont(const QFont &);
        void setValueLabelFont(const QFont *);
        void setValueLabelFont(const QFont &);
        void setValueFont(const QFont *);
        void setValueFont(const QFont &);

        void setMinValue(double);
        void setMinValue(int);
        void setMaxValue(double);
        void setMaxValue(int);

        void setReferenceLabel(int, const QString&);
        void setSetValue(int, int, double);
        void setSetColor(int, const QColor*);
        void setSetColor(int, const QColor&);

        void setDrawBars(bool);
        void setDrawLines(bool);
        void setDrawPoints(bool);

        void setAutoMinMax(bool);
        void setAutoRepaint(bool);

        void clear();

    protected:
        virtual void paintEvent(QPaintEvent*); 

        GReferences _data;

        QString _dataLabel;
        QString _valueLabel;
        QString _title;

        int _hPadding;
        int _vPadding;

        double _minValue;
        double _maxValue;

        bool _drawBars;
        bool _drawLines;
        bool _drawPoints;

        QMap<int, QColor> _setColors;

        QFont * _titleFont;
        QFont * _dataLabelFont;
        QFont * _dataFont;
        QFont * _valueLabelFont;
        QFont * _valueFont;

        bool _autoMinMax;
        bool _autoRepaint;
};

#endif

