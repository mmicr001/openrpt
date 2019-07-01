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

#ifndef __GRAPHICSSECTION_H__
#define __GRAPHICSSECTION_H__

#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QDomDocument>
#include <QList>

#include <parsexmlutils.h>

class ORGraphicsSectionItem;
class DocumentScene;

class ORSectionHandle : public QGraphicsRectItem
{
  public:
    enum { Type = UserType + 49 };

    ORSectionHandle(QGraphicsItem * parent = 0);

    int type() const { return Type; }

  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
};

class ORGraphicsSectionItem : public QGraphicsRectItem
{
  public:
    enum { Type = UserType + 50 };
    enum Highlight {
      Normal = 0,
      Origin,
      Destination
    };

    ORGraphicsSectionItem(QGraphicsItem * parent = 0);

    void setTitle(const QString & s);
    QString title() const;
    void highlightTitle(bool v);

    void buildXML(QDomDocument & doc, QDomElement & section);
    void initFromXML(QDomNode & section);

    int type() const { return Type; }

    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    void highlight(enum Highlight mode);

  protected:
    //void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);

    qreal _previousWidth;

  private:
    ORSectionHandle * _handle;
    QGraphicsSimpleTextItem * _title;
    bool _hightLighted;
};

class ORGraphicsSectionDetail;
class ORGraphicsSectionDetailGroup : public QObject
{
  Q_OBJECT

  public:
    ORGraphicsSectionDetailGroup(const QString &, ORGraphicsSectionDetail *, QObject * parent);
    ~ORGraphicsSectionDetailGroup();

    enum PageBreak
    {
      BreakNone = 0,
      BreakAfterGroupFooter = 1
    };

    void setTitle(const QString & s);
    void setColumn(const QString &);
    void showGroupHead(bool yes = true);
    void showGroupFoot(bool yes = true);
    void setPageBreak(int);

    QString getTitle() const { return _name; }
    QString column() const { return _column; }
    bool isGroupHeadShowing() const;
    bool isGroupFootShowing() const;
    int  pageBreak() const { return _pagebreak; }

    ORGraphicsSectionItem * getGroupHead() { return _head; }
    ORGraphicsSectionItem * getGroupFoot() { return _foot; }

  protected:
    QString _name;
    QString _column;

    ORGraphicsSectionItem * _head;
    ORGraphicsSectionItem * _foot;

    ORGraphicsSectionDetail * _rsd;

    int _pagebreak;
};

class ORGraphicsSectionDetail : public QObject
{
  Q_OBJECT

  public:
    ORGraphicsSectionDetail(DocumentScene * rptwin, QObject * parent);
    ~ORGraphicsSectionDetail();

    enum PageBreak
    {
      BreakNone = 0,
      BreakAtEnd = 1
    };

    void setTitle(const QString & s);
    void setQuery(const QString &);
    void setPageBreak(int);

    QString getTitle() const { return _name; }
    QString query() const { return _query; }
    int pageBreak() const { return _pagebreak; }

    ORGraphicsSectionItem * getDetail() { return _detail; }
    DocumentScene * reportWindow() { return _rw; }


    void buildXML(QDomDocument & doc, QDomElement & section);
    void initFromXML(QDomNode & node);

    int groupSectionCount() const;
    ORGraphicsSectionDetailGroup * getSection(int i);
    void insertSection(int idx, ORGraphicsSectionDetailGroup * rsd);
    int findSection(const QString & name);
    void removeSection(int idx, bool del = false);

    void adjustSize();

  protected:
    QString _query;

    QString _name;
    ORGraphicsSectionItem * _detail;
    DocumentScene * _rw;

    QList<ORGraphicsSectionDetailGroup*> groupList;

    int _pagebreak;
};

#endif

