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

#include "metasqlsaveparameters.h"

#include <QMessageBox>
#include <QSqlError>

#include "parameter.h"
#include "metasql.h"
#include "xsqlquery.h"

#define DEBUG false

MetaSQLSaveParameters::MetaSQLSaveParameters(QWidget *parent,
                                             Qt::WindowFlags fl)
  : QDialog(parent, fl)
{
  setupUi(this);

  _schema->addItem("");
  _schema->addItem("public");
  XSqlQuery schemaq("SELECT pkghead_name"
                    "  FROM pkghead"
                    " ORDER BY pkghead_name;");
  schemaq.exec();
  while (schemaq.next())
    _schema->addItem(schemaq.value("pkghead_name").toString());

  connect(_schema, SIGNAL(currentIndexChanged(int)), this, SLOT(sGetGroups()));

  sGetGroups();
}

MetaSQLSaveParameters::~MetaSQLSaveParameters()
{
  // no need to delete child widgets, Qt does it all for us
}

void MetaSQLSaveParameters::languageChange()
{
    retranslateUi(this);
}

int MetaSQLSaveParameters::grade() const
{
  return _grade->value();
}

QString MetaSQLSaveParameters::group() const
{
  return _group->currentText();
}

QString MetaSQLSaveParameters::name() const
{
  return _name->text();
}

QString MetaSQLSaveParameters::notes() const
{
  return _notes->toPlainText();
}

QString MetaSQLSaveParameters::schema() const
{
  return _schema->currentText();
}

void MetaSQLSaveParameters::setGrade(int p)
{
  if (p < 0)
    _grade->setValue(-1);
  else if (p >= 99)
    _grade->setValue(99);
  else
    _grade->setValue(p);
}

void MetaSQLSaveParameters::setGroup(const QString p)
{
  int idx = _group->findText(p, Qt::MatchFixedString); // case-insensitive
  if (idx < 0)
  {
    _group->addItem(p);
    idx = _group->findText(p, Qt::MatchFixedString); // case-insensitive
  }
    
  _group->setCurrentIndex(idx);
}

void MetaSQLSaveParameters::setName(const QString p)
{
  _name->setText(p);
}

void MetaSQLSaveParameters::setNotes(const QString p)
{
  _notes->setPlainText(p);
}

void MetaSQLSaveParameters::setSchema(const QString p)
{
  if (DEBUG)
    qDebug("MetaSQLSaveParameters::setSchema(%s) entered", qPrintable(p));
  int idx = _schema->findText(p, Qt::MatchFixedString); // case-insensitive
  if (idx < 0)
    idx = _schema->findText("public", Qt::MatchFixedString); // case-insensitive
    
  _schema->setCurrentIndex(idx);
  if (DEBUG)
    qDebug("MetaSQLSaveParameters::setSchema(%s) returning with %s (%d)",
           qPrintable(p), qPrintable(_schema->currentText()), idx);
}

void MetaSQLSaveParameters::sGetGroups()
{
  ParameterList params;
  if (_schema->currentText() == "public")
    params.append("public");
  else if (! _schema->currentText().isEmpty())
    params.append("schema", _schema->currentText());

  QString groups("SELECT DISTINCT metasql_group"
                 "<? if exists(\"public\") ?>"
                 "  FROM ONLY metasql"
                 "<? elseif exists(\"schema\") ?>"
                 "  FROM <? literal(\"schema\") ?>.pkgmetasql"
                 "<? else ?>"
                 "  FROM metasql"
                 "<? endif ?>"
                 " ORDER BY metasql_group;");
  MetaSQLQuery groupm(groups);
  XSqlQuery groupq = groupm.toQuery(params);
  groupq.exec();
  _group->clear();
  _group->addItem("");
  while (groupq.next())
    _group->addItem(groupq.value("metasql_group").toString());
  if (groupq.lastError().type() != QSqlError::NoError)
    QMessageBox::warning(this, tr("Database Errror"),
                         groupq.lastError().text());

  _group->setCurrentIndex(-1);
}
