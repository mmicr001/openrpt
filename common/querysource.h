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

#ifndef __QUERYSOURCE_H__
#define __QUERYSOURCE_H__

#include <QObject>
#include <QString>
#include <QList>
#include <QSqlDatabase>

class QuerySourceList;

class QuerySource
{
  public:
    QuerySource();
    QuerySource(const QString & n, const QString & q = QString::null, bool fromDb = false, const QString & mg = QString::null, const QString & mn = QString::null);
    ~QuerySource();

    void setName(const QString &);
    QString name() const;
    void setQuery(const QString &);
    QString query() const;
    void setLoadFromDb(bool);
    bool loadFromDb() const;
    void setMetaSqlGroup(const QString &);
    QString metaSqlGroup() const;
    void setMetaSqlName(const QString &);
    QString metaSqlName() const;
    void setColNames(const QStringList &);
    QStringList colNames() const;

    // This is a special overload that will return the loaded query
    // if that is what is needed or the specified query otherwise.
    QString query(const QSqlDatabase &) const;

  private:
    QString _name;
    QString _query;
    bool    _loadFromDb;
    QString _mqlGroup;
    QString _mqlName;
    QStringList _colNames;

    friend class QuerySourceList;
    QuerySourceList *_inList;
    void updated();
};

class QuerySourceList : public QObject
{
  Q_OBJECT
  public:
    QuerySourceList(QObject * parent = 0);
    ~QuerySourceList();

    unsigned int size();

    bool add(QuerySource * qs);

    QuerySource * remove(int i);
    QuerySource * remove(QuerySource * qs);
    QuerySource * remove(const QString & name);

    QuerySource * get(int i);
    QuerySource * get(const QString & name);
    bool contains(QString name);

  signals:
    void updated();

  private:
    QList<QuerySource*> _srcList;

    friend class QuerySource;
    void childUpdated(QuerySource *);
};

#endif
