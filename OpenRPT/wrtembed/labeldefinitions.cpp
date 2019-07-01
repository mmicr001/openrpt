/*
 * This file is part of the OpenRPT report writer and rendering engine,
 * and is Copyright (c) 2001-2019 by OpenMFG LLC, d/b/a xTuple,
 * portions are Copyright (C) 2012 by Paladin Logic, Ltd.  It
 * is licensed to you under the xTuple End-User License Agreement ("the
 * EULA"), the full text of which is available at www.xtuple.com/EULA.
 * While the EULA gives you access to source code and encourages your
 * involvement in the development process, this Package is not free
 * software.  By using this software, you agree to be bound by the
 * terms of the EULA.
 */

#include "labeldefinitions.h"

#include <QVariant>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QSqlError>
#include <xsqlquery.h>
#include <labelsizeinfo.h>

//#include <querysource.h>
#include "labeldefinitioneditor.h"

LabelDefinitions::LabelDefinitions(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setupUi(this);

  // signals and slots connections
  connect(ldList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editLabelDef(QListWidgetItem*)));
  connect(btnEdit, SIGNAL(clicked()), this, SLOT(btnEdit_clicked()));
  connect(btnDelete, SIGNAL(clicked()), this, SLOT(btnDelete_clicked()));
  connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAdd_clicked()));
  connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
  connect(ldList, SIGNAL(itemSelectionChanged()), this, SLOT(sEnableButtons()));

  btnEdit->setEnabled(false);
  btnDelete->setEnabled(false);

}

LabelDefinitions::~LabelDefinitions()
{
  // no need to delete child widgets, Qt does it all for us
}

void LabelDefinitions::languageChange()
{
  retranslateUi(this);
}

void LabelDefinitions::editLabelDef(QListWidgetItem* lbitem)
{
  if(lbitem)
  {
    QString originalName = lbitem->text();
    LabelSizeInfo labelInfo = LabelSizeInfo::getByName(originalName);

    // run the editor dialog
    LabelDefinitionEditor lde(this);
    lde.init(labelInfo);

    if(lde.exec() == QDialog::Accepted)
    {
      LabelSizeInfo labelDef = lde.getLabelDefinition();

      XSqlQuery xqry;
      xqry.prepare( "UPDATE labeldef SET labeldef_name=:name, labeldef_papersize=:papersize, labeldef_columns=:columns, labeldef_rows=:rows, labeldef_width=:width, labeldef_height=:height, labeldef_start_offset_x=:offsetx, labeldef_start_offset_y=:offsety, labeldef_horizontal_gap=:hgap, labeldef_vertical_gap=:vgap WHERE labeldef_name=:original_name");

      xqry.bindValue(":name", labelDef.name());
      xqry.bindValue(":papersize", labelDef.paper());
      xqry.bindValue(":columns", labelDef.columns());
      xqry.bindValue(":rows", labelDef.rows());
      xqry.bindValue(":width", labelDef.width());
      xqry.bindValue(":height", labelDef.height());
      xqry.bindValue(":offsetx", labelDef.startX());
      xqry.bindValue(":offsety", labelDef.startY());
      xqry.bindValue(":hgap", labelDef.xGap());
      xqry.bindValue(":vgap", labelDef.yGap());
      xqry.bindValue(":original_name", originalName);

      xqry.exec();

      if (xqry.lastError().type() == QSqlError::NoError)
      {
        init();
      }
      else
      {
        QMessageBox::critical(NULL, QString("Database Error"),  xqry.lastError().databaseText());
      }
    }
  }
}

void LabelDefinitions::btnEdit_clicked()
{
  // get the selected item if any then call editLabelDef(QListBoxItem)
  int idx = ldList->currentRow();
  if(idx != -1)
  {
    editLabelDef(ldList->item(idx));
  }
}

void LabelDefinitions::btnDelete_clicked()
{
  // get the selected item in the listbox them remove it
  // from the listbox and from the LabelDefinitions
  int idx = ldList->currentRow();
  if(idx != -1)
  {
    if (QMessageBox::warning(
          this,
          tr("Delete Label Definition"),
          tr("Really delete this label definition?  This cannot be undone."),
          QMessageBox::Yes,
          QMessageBox::No | QMessageBox::Default
        ) == QMessageBox::Yes)
    {
      QListWidgetItem * item = ldList->item(idx);
      XSqlQuery delQuery;
      delQuery.prepare("DELETE FROM labeldef WHERE labeldef_name=:labelName");
      delQuery.bindValue(":labelName", item->text()); 
      delQuery.exec();

      if (delQuery.lastError().type() == QSqlError::NoError)
      {
        ldList->takeItem(idx);
      }
      else
      {
        QMessageBox::critical(NULL, QString("Database Error"),  delQuery.lastError().databaseText());
      }
    }
  }
}

void LabelDefinitions::btnAdd_clicked()
{
  // add a new querySource item
  LabelSizeInfo labelInfo;

  // run the editor dialog
  LabelDefinitionEditor lde(this);
  lde.init(labelInfo);

  if(lde.exec() == QDialog::Accepted)
  {
    LabelSizeInfo labelDef = lde.getLabelDefinition();

    XSqlQuery xqry;
    xqry.prepare( "INSERT INTO labeldef (labeldef_name, labeldef_papersize, labeldef_columns, labeldef_rows, labeldef_width, labeldef_height, labeldef_start_offset_x, labeldef_start_offset_y, labeldef_horizontal_gap, labeldef_vertical_gap) VALUES (:name, :papersize, :columns, :rows, :width, :height, :offsetx, :offsety, :hgap, :vgap )" );

    xqry.bindValue(":name", labelDef.name());
    xqry.bindValue(":papersize", labelDef.paper());
    xqry.bindValue(":columns", labelDef.columns());
    xqry.bindValue(":rows", labelDef.rows());
    xqry.bindValue(":width", labelDef.width());
    xqry.bindValue(":height", labelDef.height());
    xqry.bindValue(":offsetx", labelDef.startX());
    xqry.bindValue(":offsety", labelDef.startY());
    xqry.bindValue(":hgap", labelDef.xGap());
    xqry.bindValue(":vgap", labelDef.yGap());

    xqry.exec();

    if (xqry.lastError().type() == QSqlError::NoError)
    {
      init();
    }
    else
    {
      QMessageBox::critical(NULL, QString("Database Error"),  xqry.lastError().databaseText());
    }
  }
}

void LabelDefinitions::init( )
{
  QStringList qsLabelDefs = LabelSizeInfo::getLabelNames();
  ldList->clear();
  for(QStringList::Iterator label = qsLabelDefs.begin(); label != qsLabelDefs.end(); label++)
  {
    ldList->addItem(*label);
  }
}

void LabelDefinitions::sEnableButtons()
{
  btnEdit->setEnabled(!ldList->selectedItems().isEmpty());
  btnDelete->setEnabled(!ldList->selectedItems().isEmpty());
}

