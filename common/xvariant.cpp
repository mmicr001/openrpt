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

#include "xvariant.h"

#include <QVariant>
#include <QBitArray>
#include <QList>
#include <QStringList>

static const QChar amper = '&';
static const QChar quote = '"';
static const QChar comma = ',';
static const QChar colon = ':';
static const QChar equal = '=';

QStringList decomposeList(const QString &);

QString encodeString(const QString &);
QString decodeString(const QString &);

QString bitArrayToString(const QBitArray &);
QBitArray stringToBitArray(const QString &);

QString listToString(const QList<QVariant> &);
QList<QVariant> stringToList(const QString &);

QString stringListToString(const QStringList &);
QStringList stringToStringList(const QString &);

QString mapToString(const QMap<QString, QVariant> &);
QMap<QString, QVariant> stringToMap(const QString &);

XVariant::XVariant() {}
XVariant::~XVariant() {}

QString XVariant::encode(const QVariant & v)
{
  QString str = QString::null;
  switch(v.type())
  {
    case QVariant::BitArray:
      return bitArrayToString(v.toBitArray());

    case QVariant::List:
      return listToString(v.toList());

    case QVariant::StringList:
      return stringListToString(v.toStringList());

    case QVariant::Map:
      return mapToString(v.toMap());

    // unsupported types
    case QVariant::Bitmap:
    case QVariant::Brush:
    case QVariant::Cursor:
    case QVariant::Icon:
    case QVariant::Image:
    case QVariant::Palette:
    case QVariant::Pen:
    case QVariant::Pixmap:
    case QVariant::Point:
    case QVariant::Rect:
    case QVariant::Region:
    case QVariant::Size:
    case QVariant::SizePolicy:
      return QString::null;

    // handled by the fallthrough
    case QVariant::Invalid:
    case QVariant::String:
    case QVariant::Font:
    case QVariant::Color:
    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::Bool:
    case QVariant::Double:
    case QVariant::Date:
    case QVariant::Time:
    case QVariant::DateTime:
    case QVariant::ByteArray:
    case QVariant::KeySequence:
    case QVariant::LongLong:
    case QVariant::ULongLong:
    default:
      break;
  }
  return v.toString();
}

QVariant XVariant::decode(const QString & type, const QString & data)
{
  QVariant v(data);
  // handle a case where the type was not taken into consideration
  // in this case we will just treat the data a string
  if(type.isEmpty())
    return v;

  QVariant::Type t = QVariant::nameToType(type.toLatin1().data());
  switch(t)
  {
    case QVariant::ByteArray:
    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::Bool:
    case QVariant::Double:
    case QVariant::Date:
    case QVariant::Time:
    case QVariant::DateTime:
    case QVariant::KeySequence:
    case QVariant::Font:
    case QVariant::Color:
    case QVariant::LongLong:
    case QVariant::ULongLong:
      v.convert(t);
      break;

    case QVariant::BitArray:
      v = QVariant(stringToBitArray(data));
      break;

    case QVariant::List:
      v = QVariant(stringToList(data));
      break;

    case QVariant::Map:
      v = QVariant(stringToMap(data));
      break;

    case QVariant::StringList:
      v = QVariant(stringToStringList(data));
      break;

    // unsupported types
    case QVariant::Bitmap:
    case QVariant::Brush:
    case QVariant::Cursor:
    case QVariant::Icon:
    case QVariant::Image:
    case QVariant::Palette:
    case QVariant::Pen:
    case QVariant::Pixmap:
    case QVariant::Point:
    case QVariant::Rect:
    case QVariant::Region:
    case QVariant::Size:
    case QVariant::SizePolicy:
      v = QVariant();
      break;

    // already handled -- variant is already
    // in correct state for these types
    case QVariant::Invalid:
    case QVariant::String:
    default:
      break;
  }

  return v;
}

QString bitArrayToString(const QBitArray & ba)
{
  QString str;
  for(int pos = 0; pos < ba.size(); pos++)
  {
    if(ba.at(pos) == 1)
      str.append("1");
    else
      str.append("0");
  }
  return str;
}

QBitArray stringToBitArray(const QString & str)
{
  uint size = str.length();

  QBitArray ba(size);
  ba.fill(0);

  for(uint pos = 0; pos < size; pos++)
  {
    if(str.at(pos) == '1')
      ba.setBit(pos);
  }

  return ba;
}


QString listToString(const QList<QVariant> & list)
{
  QString str;
  QVariant v;
  for(int i = 0; i < list.size(); i++)
  {
    v = list.at(i);
    if(!str.isEmpty())
      str.append(comma);

    str.append(quote);
    str.append(encodeString(QVariant::typeToName(v.type())));
    str.append(quote);
    str.append(colon);
    str.append(quote);
    str.append(encodeString(XVariant::encode(v)));
    str.append(quote);
  }
  return str;
}

QList<QVariant> stringToList(const QString & str)
{
  QStringList tList = decomposeList(str);
  QList<QVariant> list;

  QString s;
  QString type;
  QString value;

  int pos;

  for(int i = 0; i < tList.size(); i++)
  {
    s = tList.at(i);

    pos = s.indexOf(colon);
    type = s.left(pos).trimmed();
    value = s.mid(pos+1).trimmed();
    
    if(quote == type.at(0) && quote == type.at(type.length() - 1))
      type = decodeString(type.mid(1, type.length() - 2));

    if(quote == value.at(0) && quote == value.at(value.length() - 1))
      value = decodeString(value.mid(1, value.length() - 2));

    list.append(XVariant::decode(type, value));
  }

  return list;
}

QString stringListToString(const QStringList & list)
{
  QString str;
  for(int i = 0; i < list.size(); i++)
  {
    if(!str.isEmpty())
      str.append(comma);

    str.append(quote);
    str.append(encodeString(list.at(i)));
    str.append(quote);
  }
  return str;
}

QStringList stringToStringList(const QString & str)
{
  QStringList tList = decomposeList(str);
  QStringList list;

  QString s;

  for(int i = 0; i < tList.size(); i++)
  {
    s = tList.at(i);
    if(quote == s.at(0) && quote == s.at(s.length() - 1))
      s = decodeString(s.mid(1, s.length() - 2));
    list.append(s);
  }

  return list;
}

QString mapToString(const QMap<QString, QVariant> &)
{
  // TODO

  return QString::null;
}

QMap<QString, QVariant> stringToMap(const QString &)
{
  QMap<QString, QVariant> map;

  // TODO

  return map;
}


QStringList decomposeList(const QString & str)
{
  bool in_string = false;
  int start = 0;
  int pos = 0;

  QStringList list;
  QString s;
  QChar c;
  
  for(pos = 0; pos < (int)str.length(); pos++)
  {
    c = str[pos];
    if(in_string)
    {
      if(quote == c)
        in_string = false;
    }
    else
    {
      if(quote == c)
        in_string = true;
      else if(comma == c)
      {
        s = str.mid(start, pos - start);
        list.append(s.trimmed());
        start = pos + 1;
      }
    }
  }
  if(start < (int)str.length())
  {
    s = str.mid(start, (int)str.length() - start);
    list.append(s.trimmed());
  }

  return list;
}

QString encodeString(const QString & data)
{
  QString str = data;

  str = str.replace(amper, "&amp;");
  str = str.replace(quote, "&quot;");

  return str;
}

QString decodeString(const QString & data)
{
  QString str = data;

  str = str.replace("&quot;", quote);
  str = str.replace("&amp;",  amper);

  return str;
}

