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

/*
*     This is a collection of various functions used to parse the
* different xml structures used in the Report definitions.  Most
* of these are structures that are common to several or the complex
* structures.
*/

#include <QFont>
#include "graphicsitems.h"
#include "fontutils.h"


QFont getItemFont(QGraphicsItem *gi)
{
    QFont font;
    font.setFamily("");

    if(gi->type() == ORGraphicsFieldItem::Type)
    {
        ORGraphicsFieldItem * item = static_cast<ORGraphicsFieldItem*>(gi);
        font = item->font();
    }
    else if(gi->type() == ORGraphicsTextItem::Type)
    {
        ORGraphicsTextItem * item = static_cast<ORGraphicsTextItem*>(gi);
        font = item->font();
    }
    else if(gi->type() == ORGraphicsLabelItem::Type)
    {
        ORGraphicsLabelItem * item = static_cast<ORGraphicsLabelItem*>(gi);
        font = item->font();
    }

    return font;
}


void setItemFont(QGraphicsItem *gi, const QFont &font)
{
    if(gi->type() == ORGraphicsFieldItem::Type)
    {
        ORGraphicsFieldItem * item = static_cast<ORGraphicsFieldItem*>(gi);
        item->setFont(font);
    }
    else if(gi->type() == ORGraphicsTextItem::Type)
    {
        ORGraphicsTextItem * item = static_cast<ORGraphicsTextItem*>(gi);
        item->setFont(font);
    }
    else if(gi->type() == ORGraphicsLabelItem::Type)
    {
        ORGraphicsLabelItem * item = static_cast<ORGraphicsLabelItem*>(gi);
        item->setFont(font);
    }
}


QString getItemFontFamily(QGraphicsItem *gi)
{
    return getItemFont(gi).family();
}

QString getItemFontSize(QGraphicsItem *gi)
{
    QFont font = getItemFont(gi);

    if(font.family().isEmpty()) 
        return "";

    return QString("%1").arg(font.pointSize());
}

bool getItemFontWeight(QGraphicsItem *gi)
{
    return getItemFont(gi).bold();
}

bool getItemFontStyle(QGraphicsItem *gi)
{
    return getItemFont(gi).italic();
}


void setItemFontFamily(QGraphicsItem *gi, const QString s)
{
    QFont font = getItemFont(gi);
    font.setFamily(s);
    setItemFont(gi, font);
}

void setItemFontSize(QGraphicsItem *gi, const QString s)
{
    int size = s.toInt();
    if(s<=0) 
        return;

    QFont font = getItemFont(gi);
    font.setPointSize(size);
    setItemFont(gi, font);
}

void setItemFontWeight(QGraphicsItem *gi, bool v)
{
    QFont font = getItemFont(gi);
    font.setBold(v);
    setItemFont(gi, font);
}

void setItemFontStyle(QGraphicsItem *gi, bool v)
{
    QFont font = getItemFont(gi);
    font.setItalic(v);
    setItemFont(gi, font);
}
