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

#include "selectmql.h"

#include <QSqlDatabase>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QSqlError>
#include <QTextDocument>
#include <QTextStream>

#include <parameter.h>
#include <xsqlquery.h>
#include <login.h>

#include "data.h"
#include "metasql.h"
#include "parameteredit.h"
#include "logoutput.h"
#include "resultsoutput.h"
#include "selectmql.h"

#define DEBUG false

SelectMQL::SelectMQL(QWidget* parent, Qt::WindowFlags fl)
    : QWidget(parent, fl)
{
  setupUi(this);

  connect(_buttons, SIGNAL(accepted()),              this, SLOT(sAccepted()));
  connect(_buttons, SIGNAL(rejected()),              this, SLOT(sRejected()));

  if (fl == Qt::Widget)
  {
    connect(_list, SIGNAL(triggered(const QModelIndex&)), this, SLOT(sAccepted()));
    _buttons->setVisible(false);
  }

  _schema->addItem("");
  _schema->addItem("public");
  XSqlQuery schemaq("SELECT pkghead_name"
                    "  FROM pkghead"
                    " ORDER BY pkghead_name;");
  schemaq.exec();
  while (schemaq.next())
    _schema->addItem(schemaq.value("pkghead_name").toString());

  _model = new QSqlTableModel(this);
  _list->setModel(_model);

  // must follow setting _model
  connect(_schema, SIGNAL(currentIndexChanged(int)), this, SLOT(sPopulate()));

  sPopulate();
}

SelectMQL::~SelectMQL()
{
  // no need to delete child widgets, Qt does it all for us
  delete _model;
  _model = 0;
}

void SelectMQL::languageChange()
{
  retranslateUi(this);
}

int SelectMQL::grade() const
{
  if (_list->currentIndex().isValid())
  {
    if (_list->currentIndex().sibling(_list->currentIndex().row(),
                                      _model->fieldIndex("metasql_grade")).data().isNull())
      return -1;
    return _list->currentIndex().sibling(_list->currentIndex().row(),
                                         _model->fieldIndex("metasql_grade")).data().toInt();
  }

  return -1;
}

QString SelectMQL::group() const
{
  if (_list->currentIndex().isValid())
    return _list->currentIndex().sibling(_list->currentIndex().row(),
                                         _model->fieldIndex("metasql_group")).data().toString();
  return QString::null;
}

int SelectMQL::id() const
{
  if (_list->currentIndex().isValid())
    return _list->currentIndex().sibling(_list->currentIndex().row(),
                                         _model->fieldIndex("metasql_id")).data().toInt();
  return -1;
}

QString SelectMQL::name() const
{
  if (_list->currentIndex().isValid())
    return _list->currentIndex().sibling(_list->currentIndex().row(),
                                         _model->fieldIndex("metasql_name")).data().toString();
  return QString::null;
}

QString SelectMQL::notes() const
{
  if (_list->currentIndex().isValid())
    return _list->currentIndex().sibling(_list->currentIndex().row(),
                                         _model->fieldIndex("metasql_notes")).data().toString();
  return QString::null;
}

QString SelectMQL::query() const
{
  if (_list->currentIndex().isValid())
    return _list->currentIndex().sibling(_list->currentIndex().row(),
                                         _model->fieldIndex("metasql_query")).data().toString();
  return QString::null;
}

QString SelectMQL::schema()
{
  QString returnVal;
  if (_list->currentIndex().isValid())
  {
    XSqlQuery schemaq;
    schemaq.prepare("SELECT nspname"
                    "  FROM metasql"
                    "  JOIN pg_class ON (metasql.tableoid=pg_class.oid)"
                    "  JOIN pg_namespace ON (relnamespace=pg_namespace.oid)"
                    " WHERE (metasql_id=:id);");
    schemaq.bindValue(":id", id());
    schemaq.exec();
    if (schemaq.first())
      returnVal = schemaq.value("nspname").toString();
    else if (schemaq.lastError().type() != QSqlError::NoError)
      QMessageBox::warning(this, tr("Database Error"),
                           schemaq.lastError().text());
  }

  if (DEBUG)
    qDebug("SelectMQL::schema() returning %s", qPrintable(returnVal));
  return returnVal;
}

void SelectMQL::setId(int id)
{
  QModelIndexList i = _model->match(_model->index(0, 0), Qt::EditRole,
                                    QVariant(id));
  if (DEBUG)
    qDebug("SelectMQL::setId(%d) found %d matches", id, i.size());

  if (i.size() >= 1)
    _list->setCurrentIndex(i.at(0));
}

void SelectMQL::sAccepted()
{
  emit selectedQuery(id());
}

void SelectMQL::sRejected()
{
  emit selectedQuery(-1);
}

void SelectMQL::sPopulate()
{
  if (_schema->currentText() == "public")
  {
    _model->setTable("metasql");
    _model->setFilter("metasql.tableoid IN (SELECT oid"
                      " FROM pg_class WHERE relname='metasql')");
  }
  else if (! _schema->currentText().isEmpty())
    _model->setTable(_schema->currentText() + ".pkgmetasql");
  else
    _model->setTable("metasql");

  _model->setSort(_model->fieldIndex("metasql_group"), Qt::AscendingOrder);
  _list->hideColumn(_model->fieldIndex("metasql_id"));
  _list->hideColumn(_model->fieldIndex("metasql_notes"));
  _list->hideColumn(_model->fieldIndex("metasql_query"));
  _list->hideColumn(_model->fieldIndex("metasql_lastuser"));
  _list->hideColumn(_model->fieldIndex("metasql_lastupdate"));

  _model->select();
}
