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

#ifndef LABELDEFINITIONEDITOR_H
#define LABELDEFINITIONEDITOR_H

#include <QDialog>
#include <labelsizeinfo.h>

#include "ui_labeldefinitioneditor.h"

class LabelDefinitionEditor : public QDialog, public Ui::LabelDefinitionEditor
{
    Q_OBJECT

  public:
    LabelDefinitionEditor(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~LabelDefinitionEditor();

  public slots:
    virtual void init(LabelSizeInfo);
    virtual LabelSizeInfo getLabelDefinition() { return labelDefinition; }

  protected slots:
    virtual void languageChange();
    virtual void saveLabelDef();

  protected:
    virtual bool nameExists(QString name);
    LabelSizeInfo labelDefinition;
    QStringList paperDefs;
};

#endif // LABELDEFINITIONEDITOR_H
