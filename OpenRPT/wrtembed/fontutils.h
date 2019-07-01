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

#ifndef __FONTUTILS_H__
#define __FONTUTILS_H__

#include <QGraphicsItem>

QString getItemFontFamily(QGraphicsItem *gi);
QString getItemFontSize(QGraphicsItem *gi);
bool getItemFontWeight(QGraphicsItem *gi);
bool getItemFontStyle(QGraphicsItem *gi);

void setItemFontFamily(QGraphicsItem *gi, QString s);
void setItemFontSize(QGraphicsItem *gi, QString s);
void setItemFontWeight(QGraphicsItem *gi, bool v);
void setItemFontStyle(QGraphicsItem *gi, bool v);

#endif
