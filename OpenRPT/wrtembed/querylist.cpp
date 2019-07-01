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

#include "querylist.h"

#include <QVariant>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>

#include <querysource.h>
#include "queryeditor.h"

QueryList::QueryList(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setupUi(this);

  // signals and slots connections
  connect(lbQuerys, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editQuery(QListWidgetItem*)));
  connect(btnEdit, SIGNAL(clicked()), this, SLOT(btnEdit_clicked()));
  connect(btnDelete, SIGNAL(clicked()), this, SLOT(btnDelete_clicked()));
  connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAdd_clicked()));
  connect(lbQuerys, SIGNAL(itemSelectionChanged()), this, SLOT(sEnableButtons()));
  
  btnEdit->setEnabled(false);
  btnDelete->setEnabled(false);
}

QueryList::~QueryList()
{
  // no need to delete child widgets, Qt does it all for us
}

void QueryList::languageChange()
{
  retranslateUi(this);
}

void QueryList::editQuery(QListWidgetItem* lbitem)
{
  if(lbitem)
  {
    // run the editor dialog
    QuerySource * qs = qsList->get(lbitem->text());

    if(qs == 0)
    {
      //qDebug("QueryList::editQuery(): Could not find '%s' in querylist\n",lbitem->text().latin1());
      return;
    }

    QueryEditor qe(this);
    qe.tbName->setText(qs->name());
    qe._metasql->setChecked(qs->loadFromDb());
    qe.tbQuery->setEnabled(!qs->loadFromDb());
    qe._mqlGroup->insertItem(0, qs->metaSqlGroup());
    qe._mqlGroup->setCurrentIndex(0);
    qe._mqlName->insertItem(0, qs->metaSqlName());
    qe._mqlName->setCurrentIndex(0);
    if(!qs->loadFromDb())
      qe.tbQuery->setText(qs->query());
    if(qe.exec() == QDialog::Accepted)
    {
      QString nname = qe.tbName->text();
      QString nquery = qe.tbQuery->toPlainText();
      bool mlfdb = qe._metasql->isChecked();
      QString mgroup = qe._mqlGroup->currentText();
      QString mname = qe._mqlName->currentText();
      if(qs->name() != nname)
      {
        // we changed the name of the query.
        // lets check to make sure we didn't change it to
        // something that already exists
        if(qsList->get(nname) != 0)
        {
          QMessageBox::warning(this, tr("Duplicate Name"), tr("The name you specified already exists in the list of query names."));
          return;
        }
        lbitem->setText(nname);
      }
      qs->setName(nname);
      qs->setQuery(nquery);
      qs->setLoadFromDb(mlfdb);
      qs->setMetaSqlGroup(mgroup);
      qs->setMetaSqlName(mname);
    }
  }
}

void QueryList::btnEdit_clicked()
{
  // get the selected item if any then call editQuery(QListBoxItem)
  int idx = lbQuerys->currentRow();
  if(idx != -1)
  {
    editQuery(lbQuerys->item(idx));
  }
}

void QueryList::btnDelete_clicked()
{
  // get the selected item in the listbox them remove it
  // from the listbox and from the QueryList
  int idx = lbQuerys->currentRow();
  if(idx != -1)
  {
    QListWidgetItem * item = lbQuerys->item(idx);
    QuerySource * qs = qsList->remove(item->text());
    if(qs != NULL)
      delete qs;
    lbQuerys->takeItem(idx);
  }
}

void QueryList::btnAdd_clicked()
{
  // add a new querySource item
  QueryEditor qe(this);
  if(qe.exec() == QDialog::Accepted)
  {
    QString nname = qe.tbName->text();
    QString nquery = qe.tbQuery->toPlainText();
    bool nmql = qe._metasql->isChecked();
    QString mgroup = qe._mqlGroup->currentText();
    QString mname  = qe._mqlName->currentText();
    QuerySource * qs = new QuerySource(nname, nquery, nmql, mgroup, mname);
    if(qsList->add(qs) == true)
    {
      lbQuerys->addItem(nname);
    }
    else
    {
      // The item was not inserted for some reason
      qDebug("Failed to insert into into QuerySourceList");
      delete qs;
    }
  }
}

void QueryList::init( QuerySourceList * qsl )
{
  qsList = qsl;
  lbQuerys->clear();
  for(unsigned int i = 0; i < qsList->size(); i++)
  {
    lbQuerys->addItem(QString(qsList->get(i)->name()));
  }
}

void QueryList::sEnableButtons()
{
  btnEdit->setEnabled(!lbQuerys->selectedItems().isEmpty());
  btnDelete->setEnabled(!lbQuerys->selectedItems().isEmpty());
}
