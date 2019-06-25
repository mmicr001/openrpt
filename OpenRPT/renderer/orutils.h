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
#ifndef __ORUTILS_H__
#define __ORUTILS_H__

#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlField>
#include <xsqlquery.h>
#include <parameter.h>

//
// These classes are used by the original orRender class and the new
// ORPreRenderer class as internal structures for processing. There is
// no need to have or use these classes otherwise.
//


//
// Private class definitions
// These classes are convienience classes just used here
// so there is no need to expose them to the outside
//
//  Query Class
class orQuery {
  private:
    QString      qstrName;

    QString      qstrQuery;
    XSqlQuery   *qryQuery;

    QSqlDatabase _database;

  public:
    orQuery();
    orQuery(const QString &, const QString &, ParameterList, bool doexec, QSqlDatabase pDb = QSqlDatabase());

    virtual ~orQuery();

    inline bool queryExecuted() const { return (qryQuery != 0); }
    bool execute();

    inline XSqlQuery *getQuery() { return qryQuery; }
    inline const QString &getSql() const { return qstrQuery; }
    inline const QString &getName() const { return qstrName; }

    QStringList     missingParamList;
};


// Data class
class orData {
  private:
    orQuery *qryThis;
    QString qstrField;
    QString qstrValue;
    QByteArray qbaValue;
    bool    _valid;

  public:
    orData();

    void  setQuery(orQuery *qryPassed);
    void  setField(const QString &qstrPPassed);

    inline bool  isValid() const { return _valid; }

    const QString &getValue();
	const QVariant getVariant() const;
    const QByteArray &getByteValue();
    const int getType();
};

#endif // __ORUTILS_H__

