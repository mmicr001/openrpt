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

#include "parameter.h"
#include <QtDebug>

Parameter::Parameter()
{
}

Parameter::Parameter(const QString &pName, const QVariant &pValue)
{
  _name  = pName;
  _value = pValue;
}

Parameter::Parameter(const Parameter &pParam)
{
  _name  = pParam._name;
  _value = pParam._value;
}

Parameter & Parameter::operator= (const Parameter &pParam)
{
  _name  = pParam._name;
  _value = pParam._value;

  return *this;
}

void ParameterList::append(const QString &pName)
{
  append(Parameter(pName, QVariant()));
}

void ParameterList::append(const QString &pName, const QVariant &pValue)
{
  append(Parameter(pName, pValue));
}

void ParameterList::append(const QString &pName, const QString &pValue)
{
  append(Parameter(pName, pValue));
}

void ParameterList::append(const QString &pName, const char *pValue)
{
  append(Parameter(pName, QString(pValue)));
}

void ParameterList::append(const QString &pName, const QDate &pValue)
{
  append(Parameter(pName, QVariant(pValue)));
}

void ParameterList::append(const QString &pName, unsigned int pValue)
{
  append(Parameter(pName, pValue));
}

void ParameterList::append(const QString &pName, int pValue)
{
  append(Parameter(pName, pValue));
}

void ParameterList::append(const QString &pName, double pValue)
{
  append(Parameter(pName, pValue));
}

void ParameterList::append(const Parameter &pParam)
{
  QList<Parameter>::append(pParam);
}

void ParameterList::remove( QString &pParamName)
{
	int remove = -1;
	for (int counter = 0; counter < count(); counter++)
	{
		if (operator[](counter)._name == pParamName)
		{
			remove = counter;
		}
	}

	if (remove > 0)
	{    
		removeAt(remove);
	}
}

QString ParameterList::name(int pAt) const
{
  return operator[](pAt)._name;
}

QVariant ParameterList::value(int pAt, bool *pValid) const
{
  if (pValid != NULL)
    *pValid = true;

  return operator[](pAt)._value;
}

QVariant ParameterList::value(const QString &pParamName, bool *pValid) const
{
  for (int counter = 0; counter < count(); counter++)
  {
    if (operator[](counter)._name == pParamName)
    {
      if (pValid != NULL)
        *pValid = true;

      return operator[](counter)._value;
    }
  }

  if (pValid != NULL)
    *pValid = false;

  return QVariant();
}

bool ParameterList::inList(const QString &pParamName) const
{
  for (int counter = 0; counter < count(); counter++)
  {
    if (operator[](counter)._name == pParamName)
      return true;
  }

  return false;
}

