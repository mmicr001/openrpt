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

#ifndef __PAGESIZEINFO_H__
#define __PAGESIZEINFO_H__

#include <qstring.h>
#include <qstringlist.h>

class PageSizeInfo
{
  public:
    PageSizeInfo(const QString&, int, int, int);
    PageSizeInfo();
    virtual ~PageSizeInfo();

    const QString & name() const;
    int qpValue() const;
    int width() const;
    int height() const;
    int area() const;

    bool isNull() const;

    static const PageSizeInfo & getByName(const QString &);
    static const PageSizeInfo & getByValue(int);
    static const PageSizeInfo & findNearest(int, int);
    static QStringList getPageNames();

  protected:
    QString _name;
    int _qpValue;
    int _width;
    int _height;

    int _area;
    bool _null;
};

#endif
