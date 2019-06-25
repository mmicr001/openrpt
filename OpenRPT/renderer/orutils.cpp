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

#include "orutils.h"

#include "../../MetaSQL/metasql.h"

//
// Class orQuery implementations
//
orQuery::orQuery()
{
  qryQuery = 0;
}

orQuery::orQuery( const QString &qstrPName, const QString &qstrSQL,
                  ParameterList qstrlstParams, bool doexec, QSqlDatabase pDb )
{
  QString qstrParsedSQL(qstrSQL);
  QString qstrParam;
  int     intParamNum;
  int     intStartIndex = 0;

  qryQuery = 0;
  _database = pDb;

  //  Initialize some privates
  qstrName  = qstrPName;

  QRegExp rexp("<\\?.*\\?>");
  if(rexp.indexIn(qstrParsedSQL) == -1)
  {
    // Parse through the passed SQL populating the parameters
    QRegExp re("(?:%(\\d+))|(?:\\$\"([^\"]*)\")");
    while ((intStartIndex = re.indexIn(qstrParsedSQL,intStartIndex)) != -1)
    {
      QString val = " ";

      QString match = re.cap(0);
      if(match[0] == '$')
      {
        QString n = re.cap(2).toLower();
        val = qstrlstParams.value(n).toString();
        if(val.isNull())
        {
          // add this to the list of missing parameters
          if(!missingParamList.contains(n))
            missingParamList.append(n);
        }
      }
      else if(match[0] == '%')
      {
        //  Grab the parameter number
        intParamNum = re.cap(1).toInt();

        //  Replace the parameter hold with the specified paramemter
        //  Verify the parameter index
        if (intParamNum <= (int)qstrlstParams.count())
          val = qstrlstParams.value(intParamNum - 1).toString();
        else
        {
          // add this to the list of missing parameters
          QString s = QString("%%1").arg(intParamNum);
          if(!missingParamList.contains(s)) missingParamList.append(s);
        }
      }
      else
      {
        // ?!?!? How did we get here.
        qDebug("Match did not start with $ or %%...");
      }

      QString qstrWork = qstrParsedSQL.left(intStartIndex)
                       + val
                       + qstrParsedSQL.right(qstrParsedSQL.length() - intStartIndex - re.matchedLength());
      intStartIndex += val.length();
      qstrParsedSQL = qstrWork;
    }

    qstrQuery = qstrParsedSQL;

    if(doexec)
      execute();
  }
  else
  {
    qstrQuery = qstrParsedSQL;
    MetaSQLQuery mql(qstrParsedSQL);
    qryQuery = new XSqlQuery(mql.toQuery(qstrlstParams, _database, doexec));
    if (doexec)
      qryQuery->first();
    // TODO: actually look for missing parameters?
  }
}

orQuery::~orQuery()
{
  if(qryQuery != 0)
  {
    delete qryQuery;
    qryQuery = 0;
  }
}

bool orQuery::execute()
{
  if(qryQuery == 0)
  {
    qryQuery  = new XSqlQuery(qstrQuery, _database);
    return qryQuery->first();
  }
  return false;
}

//
// Class orData
//
orData::orData()
{
  _valid = false;
  qryThis = 0;
}

void orData::setQuery(orQuery *qryPassed)
{
  qryThis = qryPassed;

  if (qstrField.length())
    _valid = true;
}

void orData::setField(const QString &qstrPPassed)
{
  qstrField = qstrPPassed;

  if (qryThis != 0)
    _valid = true;
}

const QString &orData::getValue()
{
  if (_valid)
    qstrValue = qryThis->getQuery()->value(qstrField).toString();

  return qstrValue;
}


const QVariant orData::getVariant() const
{
	QVariant v;
	if (_valid)
		v = qryThis->getQuery()->value(qstrField);

	return v;
}

const QByteArray &orData::getByteValue()
{
  if (_valid)
  {
    qbaValue = qryThis->getQuery()->value(qstrField).toByteArray();
  }

  return qbaValue;
}

const int orData::getType()
{
  int type;
  if (_valid)
  {
      QSqlField field = qryThis->getQuery()->record().field(qstrField);
      type = field.type();
  }

  return type;
}
