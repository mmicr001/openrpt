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

#include <QString>
#include <QVariant>

#include <parameter.h>

#include <QSqlDatabase>

#include "metasql.h"

#include <string>
#include <map>

#include "metasqlqueryparser.h"

class MetaSQLInfoQt : public MetaSQLInfo {
    public:
        MetaSQLInfoQt(const ParameterList & params) : MetaSQLInfo() {
            _params = &params;
            _paramCount = 0;
        }

        virtual std::list<std::string> enumerateNames() {
            std::list<std::string> names;
            for(int n = 0; n < _params->count(); n++) {                                                                
                names.push_back(_params->name(n).toStdString());                                               
            }
            return names;
        }
        virtual bool isValueFirst(const std::string & name) {
            return getValuePos(name) == 0;
        }
        virtual bool isValueLast(const std::string & name) {
            return getValuePos(name) == (getValueListCount(name) - 1);
        }
        virtual int getValueListCount(const std::string & name) {
            bool found = false;
            QVariant v = _params->value(QString::fromStdString(name), &found);
            int lc = 0;
            if(found && (v.type() == QVariant::List || v.type() == QVariant::StringList)) {
                lc = v.toList().count();
            }
            return lc;
        }
	virtual std::string getValue(const std::string & name, bool param = false, int pos = -1) {
            bool found = false;
            QVariant v = _params->value(QString::fromStdString(name), &found);
            if(found && (v.type() == QVariant::List || v.type() == QVariant::StringList)) {
                v = v.toList().at((pos == -1 ? getValuePos(name) : pos));
            }
            if(param) {
                _paramCount++;
                std::stringstream sstr;
                sstr << ":_" << _paramCount << "_";
                std::string n = sstr.str();
                _pList[n] = v;
                return n + " ";
            } else {
                return v.toString().toStdString();
            }
        }

        std::map<std::string,QVariant> _pList;
        int _paramCount;
        const ParameterList * _params;
};

MetaSQLQuery::MetaSQLQuery(const QString & query) {
    _data = new MetaSQLQueryParser();
    _source = QString::null;

    if(!query.isEmpty()) {
        setQuery(query);
    }
}

MetaSQLQuery::~MetaSQLQuery() {
    if(_data) {
        delete _data;
        _data = 0;
    }
}

bool MetaSQLQuery::setQuery(const QString & query) {
    bool valid = false;
    if(_data) {
        _source = query;
        valid = _data->parse_query(query.toStdString());
    }
    return valid;
}

QString MetaSQLQuery::getSource() { return _source; }
bool MetaSQLQuery::isValid() { return (_data && _data->isValid()); }

XSqlQuery MetaSQLQuery::toQuery(const ParameterList & params, QSqlDatabase pDb, bool pExec) {
    XSqlQuery qry(pDb);
    if(isValid()) {
        MetaSQLInfoQt mif(params);
        if(qry.prepare(QString::fromStdString(_data->populate(&mif)))) {
            for ( std::map<std::string, QVariant>::iterator it=mif._pList.begin() ; it != mif._pList.end(); it++ ) {
                qry.bindValue(QString::fromStdString((*it).first) ,(*it).second);
            }
            if(pExec) {
                qry.exec();
            }
        }
    }
    return qry;
}

QString MetaSQLQuery::parseLog() { return (_data ? QString::fromStdString(_data->errors()) : QString::null); }

