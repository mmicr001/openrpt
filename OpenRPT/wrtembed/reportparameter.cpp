/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2018 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
 */

#include "reportparameter.h"

#include <QButtonGroup>
#include <QVariant>
#include <QTableWidgetItem>
#include "reportparameterlistitem.h"

ReportParameter::ReportParameter(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);

    QButtonGroup * buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(_staticList, 0);
    buttonGroup->addButton(_dynamicList, 1);

    // signals and slots connections
    connect(_btnOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(buttonGroup, SIGNAL(buttonClicked(int)), _stack, SLOT(setCurrentIndex(int)));
    connect(_listValues, SIGNAL(itemSelectionChanged()), this, SLOT(sSelectionChanged()));
    connect(_add, SIGNAL(clicked()), this, SLOT(sAdd()));
    connect(_edit, SIGNAL(clicked()), this, SLOT(sEdit()));
    connect(_remove, SIGNAL(clicked()), this, SLOT(sRemove()));
    connect(_mqlParams, SIGNAL(currentIndexChanged(int)), this, SLOT(sUpdateName()));
}

ReportParameter::~ReportParameter()
{
    // no need to delete child widgets, Qt does it all for us
}

void ReportParameter::languageChange()
{
    retranslateUi(this);
}

static const char* types[] = { "string", "integer", "double", "bool", NULL };

QString ReportParameter::paramName()
{
    return _mqlParams->currentText();
}


ORParameter ReportParameter::paramData()
{
  ORParameter param;

  param.name = _mqlParams->currentText();
  param.type = QString(types[_cbType->currentIndex()]);
  param.defaultValue = _leDefault->text();
  param.description = _tbDescrip->toPlainText();
  param.active = _active->isChecked();
  if(_staticList->isChecked())
  {
    param.listtype = "static";
    for(int i = 0; i < _listValues->topLevelItemCount(); ++i)
    {
      QTreeWidgetItem * item = _listValues->topLevelItem(i);
      param.values.append(qMakePair(item->text(0), item->text(1)));
    }
  }
  else // if(_dynamicList->isChecked())
  {
    param.listtype = "dynamic";
    param.query = _dynamicQuery->toPlainText();
  }

  return param;
}

void ReportParameter::setParamData( const ORParameter & param)
{
  for(int i = 0; types[i] != NULL; i++)
  {
    if(types[i] == param.type)
    {
      _cbType->setCurrentIndex(i);
      break;
    }
  }
  if(_mqlParams->count()==0)
    _mqlParams->addItem(param.name);

  _tbDescrip->setText(param.description);
  _active->setChecked(param.active);
  _leDefault->setText(param.defaultValue);
  if(param.listtype == "static")
  {
    _staticList->setChecked(true);
    _stack->setCurrentIndex(0);
    for(QList<QPair<QString,QString> >::const_iterator it = param.values.begin();
        it != param.values.end(); it++ )
      new QTreeWidgetItem(_listValues, QStringList() << (*it).first << (*it).second);
  }
  else //if(param.listtype == "dynamic")
  {
    _dynamicList->setChecked(true);
    _stack->setCurrentIndex(1);
    _dynamicQuery->setText(param.query);
  }
}


void ReportParameter::sSelectionChanged()
{
  bool yes = (_listValues->currentItem() != 0);
  _edit->setEnabled(yes);
  _remove->setEnabled(yes);
}


void ReportParameter::sAdd()
{
  ReportParameterListItem newdlg(this);
  if(newdlg.exec() == QDialog::Accepted)
    new QTreeWidgetItem(_listValues, QStringList() << newdlg._value->text() << newdlg._label->text());
}


void ReportParameter::sEdit()
{
  QTreeWidgetItem * item = _listValues->currentItem();
  if(0 != item)
  {
    ReportParameterListItem newdlg(this);
    newdlg._value->setText(item->text(0));
    newdlg._label->setText(item->text(1));
    if(newdlg.exec() == QDialog::Accepted)
    {
      item->setText(0, newdlg._value->text());
      item->setText(1, newdlg._label->text());
    }
  }
}


void ReportParameter::sRemove()
{
  QTreeWidgetItem * item = _listValues->currentItem();
  if(0 != item)
    delete item;
}

void ReportParameter::setQueryList( QuerySourceList* qlist )
{
  qsList = qlist;
}

void ReportParameter::setMap(QMap<QString,ORParameter> *map)
{
  _map = map;
}

void ReportParameter::setMode(QString mode)
{
  _mode=mode;
  if (_mode=="new")
  {
    this->populateMqlParams();
  }
  else if (_mode=="edit")
  {
    _mqlParams->setEnabled(false);
  }
}

void ReportParameter::populateMqlParams()
{
  QStringList params; 
  for(int i=0; i < qsList->size(); i++)
  {
    foreach(QString p,getParamsFromText(qsList->get(i)->query()) )
    {
      if (!_map->contains(p))
        params << p;    
    }
  }

  params.removeDuplicates();
  foreach(QString param, params)
    _mqlParams->addItem(param);
}

void ReportParameter::sUpdateName()
{
  if(_mqlParams->currentIndex()!=0)
  {
    if(_map->contains(_mqlParams->currentText()))
      setParamData(_map->value(_mqlParams->currentText()));
  }
}
