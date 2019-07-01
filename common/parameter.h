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

#ifndef parameter_h
#define parameter_h

#include <QList>
#include <QPair>
#include <QString>
#include <QVariant>

class ParameterList;

class Parameter
{
  friend class ParameterList;

  public:
    Parameter();
    Parameter(const QString &, const QVariant &);
    Parameter(const Parameter &);

    Parameter & operator= (const Parameter &);

inline
    QString  name() const  { return _name;   };
inline
    QVariant value() const { return _value;  };

  protected:
    QString  _name;
    QVariant _value;
};

class ParameterList : public QList<Parameter>
{
  public:
    void append(const QString &);
    void append(const QString &, const QVariant &);
    void append(const QString &, const QString &);
    void append(const QString &, const char *);
    void append(const QString &, const QDate &);
    void append(const QString &, unsigned int);
    void append(const QString &, int);
    void append(const QString &, double);
    void append(const Parameter &);

	void remove( QString &);

    QString  name(int) const;
    QVariant value(int, bool * = NULL) const;
    QVariant value(const QString &, bool * = NULL) const;
    bool     inList(const QString &) const;
};
  
#endif

