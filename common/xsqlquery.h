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

#ifndef __XSQLQUERY_H__
#define __XSQLQUERY_H__

#include <QSqlQuery>

class XSqlQueryPrivate;
class QSqlError;


class XSqlQueryErrorListener {
  public:
    XSqlQueryErrorListener();
    virtual ~XSqlQueryErrorListener();
    virtual void error(const QString &, const QSqlError&) = 0;
};

class XSqlQuery : public QSqlQuery
{
  public:
    XSqlQuery();
    XSqlQuery(QSqlDatabase);
    XSqlQuery(QSqlResult *);
    XSqlQuery(const QString &, QSqlDatabase = QSqlDatabase());
    XSqlQuery(const QSqlQuery &);
    XSqlQuery(const XSqlQuery &);
    virtual ~XSqlQuery();
    XSqlQuery & operator=(const XSqlQuery &);

    virtual QVariant value(int i) const;
    virtual QVariant value(const QString &) const;

    virtual bool first();
    virtual bool next();
    virtual bool previous();
    virtual bool prev();

    virtual int count();

    virtual bool prepare(const QString &);

    virtual bool exec();
    bool exec(const QString &);

    virtual int findFirst(int, int);
    virtual int findFirst(const QString &, int);
    virtual int findFirst(const QString &, const QString &);

    void trackFieldTotal(QString &);
    double getFieldTotal(QString &);
    double getFieldSubTotal(QString &);
    void resetSubTotals();
    void resetSubTotalsCurrent();

    bool emulatePrepare() const;
    void setEmulatePrepare(bool);

    static void addErrorListener(XSqlQueryErrorListener*);
    static void removeErrorListener(XSqlQueryErrorListener*);
    static void setNameErrorValue(QString v);

  private:
    XSqlQueryPrivate * _data;
};

#endif
