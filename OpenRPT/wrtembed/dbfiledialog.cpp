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

#include "dbfiledialog.h"
#include "builtinSqlFunctions.h"

#include <QSqlDatabase>
#include <QSqlError>
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
    if (qry.lastError().isValid())
    {
      QMessageBox::warning( this, tr("Unable to list reports correctly"),
                            qry.lastError().databaseText());
      return;
    }

    _package->addItem("");

    qry.exec(getSqlFromTag("fmt21", QSqlDatabase::database().driverName()));
    while(qry.next())
    {
      _package->addItem(qry.value("package").toString());
    }
    if (qry.lastError().isValid())
    {
      QMessageBox::warning( this, tr("Unable to get schemas containing reports"),
                            qry.lastError().databaseText());
      return;
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


