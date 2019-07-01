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

#include "builtinformatfunctions.h"

static const int __fieldTag = 0;
static const int __fieldName = 1;
static const int __fieldFunction = 2;

static const int __fieldCount = 3;

static const char* __builtinTable[][__fieldCount] = {
//{"tag",        "Name",           "sqlFunctionName"}
  {"qty",        "Quantity",       "formatQty"},
  {"qtyper",     "Quantity Per",   "formatQtyPer"},

  {"extprice",   "Ext. Price",     "formatExtPrice"},
  {"purchprice", "Purchase Price", "formatPurchPrice"},
  {"salesprice", "Sales Price",    "formatSalesPrice"},
  {"price",      "Price",          "formatPrice"},
  {"cost",       "Cost",           "formatCost"},
  {"money",      "Money",          "formatMoney"},

  {"percent",    "Percent",        "formatPrcnt"},
  {"weight",     "Weight",         "formatWeight"},
  {"ratio",      "Ratio",          "formatRatio"},
  {"uomratio",   "UOM Ratio",      "formatUOMRatio"},
  {"scrap",      "Scrap",          "formatScrap"},

  {0,            0,                0} // DO NOT REMOVE -- null record
};



QStringList getTagList()
{
  QStringList tags;

  for (int i = 0; __builtinTable[i][__fieldTag] != 0; i++)
    tags.append(__builtinTable[i][__fieldTag]);

  return tags;
}

QStringList getNameList()
{
  QStringList names;

  for (int i = 0; __builtinTable[i][__fieldTag] != 0; i++)
    names.append(__builtinTable[i][__fieldName]);

  return names;
}


QString getNameFromTag(const QString & str)
{
  for (int i = 0; __builtinTable[i][__fieldTag] != 0; i++)
    if (__builtinTable[i][__fieldTag] == str)
      return __builtinTable[i][__fieldName];

  return QString::null;
}

QString getFunctionFromTag(const QString & str)
{
  for (int i = 0; __builtinTable[i][__fieldTag] != 0; i++)
    if (__builtinTable[i][__fieldTag] == str)
      return __builtinTable[i][__fieldFunction];

  return QString::null;
}

QString getTagFromName(const QString & str)
{
  for (int i = 0; __builtinTable[i][__fieldTag] != 0; i++)
    if (__builtinTable[i][__fieldName] == str)
      return __builtinTable[i][__fieldTag];

  return QString::null;
}

