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

#ifndef __REPORTPAGEOPTIONS_H__
#define __REPORTPAGEOPTIONS_H__

#include <qobject.h>
#include <qstring.h>

class ReportPageOptions : public QObject
{
  Q_OBJECT
  public:
    ReportPageOptions();
    ReportPageOptions(const ReportPageOptions &);

    ReportPageOptions & operator=(const ReportPageOptions &);

    enum PageOrientation {
      Landscape = 0, // essentially false
      Portrait = 1   // and true
    };

    double getMarginTop() const;
    void setMarginTop(double v);
    double getMarginBottom() const;
    void setMarginBottom(double v);
    double getMarginLeft() const;
    void setMarginLeft(double v);
    double getMarginRight() const;
    void setMarginRight(double v);

    const QString & getPageSize() const;
    void setPageSize(const QString & s);
    double getCustomWidth() const;
    void setCustomWidth(double v);
    double getCustomHeight() const;
    void setCustomHeight(double v);

    PageOrientation getOrientation() const;
    bool isPortrait() const;
    void setOrientation(PageOrientation o);
    void setPortrait(bool yes);

    void setLabelType(const QString &);
    const QString & getLabelType() const;
    
  signals:
    void pageOptionsChanged();

  private:
    double _marginTop;
    double _marginBottom;
    double _marginLeft;
    double _marginRight;

    QString _pagesize;
    double _customWidth;
    double _customHeight;

    PageOrientation _orientation;

    QString _labelType;
};

#endif
