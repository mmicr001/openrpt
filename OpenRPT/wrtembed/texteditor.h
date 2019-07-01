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

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QDialog>

#include "ui_texteditor.h"

class TextEditor : public QDialog, public Ui::TextEditor
{
    Q_OBJECT

public:
    TextEditor(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~TextEditor();

public slots:
    virtual void rbAlign_changed();
    virtual void btnFont_clicked();
    virtual void tbText_textChanged(const QString & Str);
    virtual void setLabelFlags(int f);
    virtual void rbHAlignNone_clicked();

protected slots:
    virtual void languageChange();

};

#endif // TEXTEDITOR_H
