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

#ifndef __LABELSIZEINFO_H__
#define __LABELSIZEINFO_H__

#include <qstring.h>
#include <qstringlist.h>

class LabelSizeInfo
{
  public:
    LabelSizeInfo(const QString&, const QString&, int, int, int, int, int, int, int, int);
    LabelSizeInfo();
    virtual ~LabelSizeInfo();

    const QString & name() const;
    const QString & paper() const;

    int columns() const;
    int rows() const;

    int width() const;
    int height() const;

    int startX() const;
    int startY() const;

    int xGap() const;
    int yGap() const;

    bool isNull() const;

    static const LabelSizeInfo & getByName(const QString &);
    static QStringList getLabelNames();
    static bool areLabelsEditable();

  protected:
    // To maintain backwards compatibility, these functions return
    // the original, hard-coded label defs w/o connecting to db.
    static const LabelSizeInfo & getByNameNoDatabase(const QString &);
    static QStringList getLabelNamesNoDatabase();

    QString _name;
    QString _paper;

    int _columns;
    int _rows;

    int _width;
    int _height;

    int _startx;
    int _starty;

    int _xgap;
    int _ygap;

    bool _null;
};

#endif
