/*
 * This file is part of the OpenRPT report writer and rendering engine,
 * and is Copyright (c) 2001-2019 by OpenMFG LLC, d/b/a xTuple,
 * portions are Copyright (C) 2011 by Paladin Logic, Ltd.  It
 * is licensed to you under the xTuple End-User License Agreement ("the
 * EULA"), the full text of which is available at www.xtuple.com/EULA.
 * While the EULA gives you access to source code and encourages your
 * involvement in the development process, this Package is not free
 * software.  By using this software, you agree to be bound by the
 * terms of the EULA.
 */

#include "labeldefinitioneditor.h"
#include <pagesizeinfo.h>
#include <xsqlquery.h>

#include <QVariant>
#include <QKeyEvent>
#include <QMessageBox>

LabelDefinitionEditor::LabelDefinitionEditor(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setupUi(this);

  // signals and slots connections
  connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));
  connect(btnSave, SIGNAL(clicked()), this, SLOT(saveLabelDef()));

  paperSize->clear();
  QStringList pageNames = PageSizeInfo::getPageNames();

  for (QStringList::Iterator name = pageNames.begin(); name != pageNames.end(); name++)
  {
    paperSize->addItem(*name);
    paperDefs.append(*name);
  }
}

LabelDefinitionEditor::~LabelDefinitionEditor()
{
  // no need to delete child widgets, Qt does it all for us
}

void LabelDefinitionEditor::init(LabelSizeInfo labelDef)
{
  if (!labelDef.isNull())
  {
    labelName->setText(labelDef.name());
    paperSize->setCurrentIndex(paperDefs.indexOf(labelDef.paper()));
    labelColumns->setValue(labelDef.columns());
    labelRows->setValue(labelDef.rows());
    labelWidth->setValue(labelDef.width());
    labelHeight->setValue(labelDef.height());
    labelStartXOffset->setValue(labelDef.startX());
    labelStartYOffset->setValue(labelDef.startY());
    labelHorizontalGap->setValue(labelDef.xGap());
    labelVerticalGap->setValue(labelDef.yGap());
  }

  labelDefinition = labelDef;
}

void LabelDefinitionEditor::saveLabelDef()
{
  LabelSizeInfo labelDef(
                  labelName->text(),
                  paperSize->currentText(),
                  labelColumns->value(),
                  labelRows->value(),
                  labelWidth->value(),
                  labelHeight->value(),
                  labelStartXOffset->value(),
                  labelStartYOffset->value(),
                  labelHorizontalGap->value(),
                  labelVerticalGap->value()
                );

  QString name = labelName->text();
  QString errorText = "";
  bool hasError = false;

  if (name.length() > 0)
  {
    if (name.compare(labelDefinition.name()) == 0 || !nameExists(name))
    {
      labelDefinition = labelDef;
    }
    else
    {
      errorText = "This label name is already taken.  Please enter a new, unique name.";
      hasError = true;
    }
  }
  else
  {
    errorText = "You must give this label definition a name.";
    hasError = true;
  }

  if (hasError)
  {
    QMessageBox::warning(this, tr("Warning"), errorText);
  }
  else
  {
    accept();
  }
}

bool LabelDefinitionEditor::nameExists(QString name)
{
  bool exists = false;
  XSqlQuery xqry;
  xqry.prepare("SELECT labeldef_id FROM labeldef WHERE labeldef_name=:name");
  xqry.bindValue(":name", name);
  xqry.exec();

  if (xqry.first())
  {
    exists = true;
  }
  return exists;
}

void LabelDefinitionEditor::languageChange()
{
  retranslateUi(this);
}
