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

#ifndef __METASQL_H__
#define __METASQL_H__

#include <QString>

class QSqlDatabase;

#include <xsqlquery.h>
#include <parameter.h>

class MetaSQLQueryParser;
class MetaSQLQuery {
    public:
        MetaSQLQuery(const QString & = QString::null);
        virtual ~MetaSQLQuery();

        bool setQuery(const QString &);
        bool isValid();
        QString getSource();

        XSqlQuery toQuery(const ParameterList &, QSqlDatabase pDb = QSqlDatabase(), bool pExec = true);

        QString parseLog();

    private:
        MetaSQLQueryParser * _data;

        QString _source;
};

#endif

