/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2018 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
 */

#include "reportgridoptions.h"

// qt
#include <QPoint>
#include <QPointF>
#include <QDebug>

#include <math.h>

extern int dpiX;
extern int dpiY;

//
// ReportGridOptions method implementations
//
ReportGridOptions::ReportGridOptions(int rdx, int rdy, QObject * parent, const char * name)
  : QObject(parent) {
    if(name)
    setObjectName(name);
    _realDpiX = rdx;
    _realDpiY = rdy;
}

void ReportGridOptions::setVisible(bool v) {
    show_grid = v;
    emit gridOptionsChanged();
}

bool ReportGridOptions::isVisible() {
    return show_grid;
}

void ReportGridOptions::setSnap(bool yes) {
    snap_grid = yes;
    emit gridOptionsChanged();
}

bool ReportGridOptions::isSnap() {
    return snap_grid;
}


QPointF ReportGridOptions::snapPoint(const QPointF & pos) {
    double x, y;
    x = pos.x();
    y = pos.y();

    if(isSnap()) {

        double xpx = 100 * xInterval();
        double ypx = 100 * yInterval();

        int mx = (int)(x / xpx);
        int my = (int)(y / ypx);
        double dx = x - (mx * xpx);
        double dy = y - (my * ypx);

        mx = (dx < (xpx/2.0) ? mx : mx + 1);
        my = (dy < (ypx/2.0) ? my : my + 1);

        x = mx * xpx;
        y = my * ypx;
    }
    return QPointF(x,y);
}


void ReportGridOptions::show() {
    setVisible(true);
}
void ReportGridOptions::hide() {
    setVisible(false);
}

void ReportGridOptions::setXInterval(double i) {
    x_interval = i;
    double d = _realDpiX * x_interval;
    double di = ((d - floor(d)) < 0.5 ? floor(d) : (floor(d) + 1.0) );
    dpiX = (int)((di / x_interval) + 0.01);
    emit gridOptionsChanged();
}
double ReportGridOptions::xInterval() {
    return x_interval;
}
void ReportGridOptions::setYInterval(double i) {
    y_interval = i;
    double d = _realDpiY * y_interval;
    double di = ((d - floor(d)) < 0.5 ? floor(d) : floor(d) + 1.0 );
    dpiY = (int)((di / y_interval) + 0.01);
    emit gridOptionsChanged();
}
double ReportGridOptions::yInterval() {
    return y_interval;
}


