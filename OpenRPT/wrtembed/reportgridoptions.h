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

#ifndef __REPORTGRIDOPTIONS_H__
#define __REPORTGRIDOPTIONS_H__

// qt
#include <qobject.h>

// forward declarations
class QPoint;
class QPointF;


class ReportGridOptions : public QObject {
    Q_OBJECT
    public:
        ReportGridOptions(int, int, QObject* = 0, const char* = 0);

        bool isVisible();
        bool isSnap();

        double xInterval();
        double yInterval();

        QPointF snapPoint(const QPointF & pos);

    public slots:
        void setVisible(bool yes = true);
        void show();
        void hide();
        void setXInterval(double i);
        void setYInterval(double i);
        void setSnap(bool yes = true);

    signals:
        void gridOptionsChanged();

    private:
        bool show_grid;
        bool snap_grid;

        double x_interval;
        double y_interval;

        int _realDpiX;
        int _realDpiY;
};


#endif

