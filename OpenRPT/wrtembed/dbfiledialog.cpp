/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2019 by OpenMFG, LLC
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

#include "dbfiledialog.h"
#include "builtinSqlFunctions.h"

#include <QSqlDatabase>
#include <QVariant>
#include <QMessageBox>
#include <xsqlquery.h>

DBFileDialog::DBFileDialog(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);


    // signals and slots connections
    connect(_btnOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(_list, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(sSelectedReport()));
    connect(_name, SIGNAL(textChanged(const QString&)), this, SLOT(sNameChanged(const QString&)));
    connect(_list, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(accept()));
    connect(_grade, SIGNAL(valueChanged(int)), this, SLOT(sGradeChanged(int)));
    connect(_package, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(sPackageChanged(const QString&)));

    _list->setColumnCount(3);
    QStringList cnames;
    cnames << tr("Name") << tr("Grade") << tr("Package");
    QTreeWidgetItem * item = new QTreeWidgetItem(_list, cnames);
    item->setData(1, Qt::TextAlignmentRole, Qt::AlignLeft);
    item->setData(2, Qt::TextAlignmentRole, Qt::AlignRight);
    item->setData(3, Qt::TextAlignmentRole, Qt::AlignRight);

    XSqlQuery qry(getSqlFromTag("fmt12", QSqlDatabase::database().driverName()));
    while(qry.next())
    {
      QTreeWidgetItem * item = new QTreeWidgetItem(_list, QStringList() << qry.value("report_name").toString() << qry.value("report_grade").toString() << qry.value("package").toString());
      item->setData(0, Qt::UserRole, qry.value("report_id"));
    }

    _package->addItem("");

    qry.exec(getSqlFromTag("fmt21", QSqlDatabase::database().driverName()));
    while(qry.next())
    {
      _package->addItem(qry.value("package").toString());
    }
}

DBFileDialog::~DBFileDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

void DBFileDialog::languageChange()
{
    retranslateUi(this);
}

int DBFileDialog::getId()
{
  QTreeWidgetItem * item = _list->currentItem();
  if(0 == item)
    return -1;

  return item->data(0, Qt::UserRole).toInt();
}

QString DBFileDialog::getName()
{
  return _name->text();
}

int DBFileDialog::getGrade()
{
  return _grade->value();
}

QString DBFileDialog::getPackage()
{
  return _package->currentText();
}

QString DBFileDialog::getSource()
{
  int rid = getId();
  if(rid != -1) {
    XSqlQuery src_qry;
    src_qry.prepare(getSqlFromTag("fmt13", QSqlDatabase::database().driverName()));	// MANU
    src_qry.bindValue(":report_id", rid);
    src_qry.exec();
    if(src_qry.first())
      return src_qry.value("report_source").toString();
  }
  return QString::null;
}

QString DBFileDialog::getNameById()
{
  int rid = getId();
  if(rid != -1)
  {
	  XSqlQuery src_qry;
    src_qry.prepare(getSqlFromTag("fmt14", QSqlDatabase::database().driverName())); // MANU
    src_qry.bindValue(":report_id", rid);
    src_qry.exec();
	  if(src_qry.first())
	    return src_qry.value("report_name").toString();
  }
  return QString::null;
}

int DBFileDialog::getGradeById()
{
  int rid = getId();
  if(rid != -1)
  {
	  XSqlQuery src_qry;
    src_qry.prepare(getSqlFromTag("fmt15", QSqlDatabase::database().driverName()));	// MANU
    src_qry.bindValue(":report_id", rid);
    src_qry.exec();
	  if(src_qry.first())
	    return src_qry.value("report_grade").toInt();
  }
  return -1;
}

QString DBFileDialog::getPackageById()
{
  int rid = getId();
  if(rid != -1)
  {
          XSqlQuery src_qry;
    src_qry.prepare(getSqlFromTag("fmt20", QSqlDatabase::database().driverName())); // MANU
    src_qry.bindValue(":report_id", rid);
    src_qry.exec();
          if(src_qry.first())
            return src_qry.value("package").toString();
  }
  return QString::null;
}

void DBFileDialog::sSelectedReport()
{
  _name->setText(getNameById());
  _name->end(false);
  _grade->setValue(getGradeById());
#if QT_VERSION >= 0x050000
  _package->setCurrentText(getPackageById());
#else
  _package->setCurrentIndex(_package->findText(getPackageById()));
#endif
}

void DBFileDialog::sNameChanged( const QString & )
{
  sNameGradePackageChanged();
}

void DBFileDialog::sGradeChanged( int )
{
  sNameGradePackageChanged();
}

void DBFileDialog::sPackageChanged( const QString & )
{
  sNameGradePackageChanged();
}

void DBFileDialog::sNameGradePackageChanged()
{
  QString name  = getName();
  QString grade = QString("%1").arg(getGrade());
  QString package = getPackage();
  QTreeWidgetItem * item = 0;
  for(int i = 0; i < _list->topLevelItemCount(); i++)
  {
    item = _list->topLevelItem(i);
    if(item->text(0) == name && item->text(1) == grade && item->text(2) == package)
    {
      _list->setCurrentItem(item);
      return;
    }
  }
  if(_list->currentItem())
    _list->currentItem()->setSelected(false);
}


