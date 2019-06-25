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

#ifndef FIELDEDITOR_H
#define FIELDEDITOR_H

#include <QDialog>

#include "ui_fieldeditor.h"
#include "documentscene.h"

class FieldEditor : public QDialog, public Ui::FieldEditor
{
    Q_OBJECT

public:
    FieldEditor(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~FieldEditor();

public slots:
    virtual void rbAlign_changed();
    virtual void btnFont_clicked();
    virtual void tbText_textChanged(const QString & Str);
    virtual void setLabelFlags(int f);
    virtual void rbHAlignNone_clicked();
    virtual void setDocScene(DocumentScene * scene);
    virtual void populateColumns();

protected slots:
    virtual void languageChange();

private:
  DocumentScene * ds;
};

#endif // FIELDEDITOR_H
