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

#ifndef __METASQLQUERYPARSER_H__
#define __METASQLQUERYPARSER_H__

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>

class MetaSQLBlock;

class MetaSQLInfo {
    public:
        MetaSQLInfo() {}
        virtual ~MetaSQLInfo() {}

        virtual std::string trueValue() { return "true"; }
        virtual std::string falseValue() { return "false"; }

        virtual void setValuePos(const std::string & name, int pos) {
            _posList[name] = pos;
        }

        virtual int getValuePos(const std::string & name) {
            int pos = 0;
            if(_posList.count(name) > 0)
              pos = _posList[name];
            return pos;
        }

        virtual std::list<std::string> enumerateNames() = 0;
        virtual bool isValueFirst(const std::string &) = 0;
        virtual bool isValueLast(const std::string &) = 0;
        virtual int getValueListCount(const std::string &) = 0;
        virtual std::string getValue(const std::string &, bool = false, int = -1) = 0;

    protected:
        std::map<std::string, int> _posList;
};

class MetaSQLInfoDefault : public MetaSQLInfo {
    public:
        MetaSQLInfoDefault() : MetaSQLInfo() {}
        virtual ~MetaSQLInfoDefault() {}

        virtual std::list<std::string> enumerateNames() {
            std::list<std::string> names;
            std::map<std::string, std::vector<std::string> >::iterator it;
            for ( it=_values.begin() ; it != _values.end(); it++ )
                names.push_back((*it).first);
            return names;
        }

        virtual bool isValueFirst(const std::string & name) {
            return getValuePos(name) == 0;
        }

        virtual bool isValueLast(const std::string & name) {
            return getValuePos(name) == (getValueListCount(name) - 1);
        }

        virtual int getValueListCount(const std::string & name) {
            std::list<std::string> list = enumerateNames();
            std::list<std::string>::iterator strlit = find(list.begin(), list.end(), name);
            int lc = 0;
            if(strlit != list.end()) {
                lc = _values[name].size();
            }
            return lc;
        }

        virtual std::string getValue(const std::string & name, bool param = false, int pos = -1) {
            std::list<std::string> list = enumerateNames();
            std::list<std::string>::iterator strlit = find(list.begin(), list.end(), name);
            std::string v;
            if(strlit != list.end()) {
                v = _values[name].at((pos == -1 ? getValuePos(name) : pos));
            }
            if(param) {
                std::string n = "'";
                std::string::iterator it;
                for(it=v.begin() ; it < v.end(); it++ ) {
                    if((*it) == '\'') n += '\'';
                    if((*it) == '\\') n += '\\';
                    n += (*it);
                }
                n += "'";
                return n;
            } else {
                return v;
            }
        }

        void setValue(const std::string & name, const std::string & value) {
            std::vector<std::string> list;
            list.push_back(value);
            setList(name, list);
        }

        void setList(const std::string &name, const std::vector<std::string> & list) {
            setValuePos(name, 0);
            _values[name] = list;
        }

    protected:
        std::map<std::string, std::vector<std::string> > _values;
};

class MetaSQLQueryParser { 
    public:
        MetaSQLQueryParser() {
            _valid = false;
            _top = 0;
        }
        virtual ~MetaSQLQueryParser();

        bool isValid() { return _valid; }
        std::string errors() const { return _logger.str(); }

        bool parse_query(const std::string & query);

        std::string populate(MetaSQLInfo *);

        std::stringstream _logger;

    private:
        bool _valid;
        MetaSQLBlock * _top;

};

#endif // __METASQLQUERYPARSER_H__
