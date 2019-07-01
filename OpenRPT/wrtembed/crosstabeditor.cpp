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

#include "crosstabeditor.h"

#include <QVariant>
#include <QFontDialog>
#include <QValidator>

#include <builtinformatfunctions.h>

/*
 *  Constructs a CrossTabEditor as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CrossTabEditor::CrossTabEditor(QWidget* parent)
    : QDialog(parent)
{
    setupUi(this);


    // signals and slots connections
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnFont, SIGNAL(clicked()), this, SLOT(btnFont_clicked()));
}

CrossTabEditor::~CrossTabEditor()
{
    // no need to delete child widgets, Qt does it all for us
}

void CrossTabEditor::languageChange()
{
    retranslateUi(this);
}

void CrossTabEditor::btnFont_clicked()
{
    // pop up a font dialog
    bool ok;
    QFont font = QFontDialog::getFont(&ok, _font, this);
    if(ok) {
        _font = font;
    }
}

void CrossTabEditor::on_valueQueryGroupBox_toggled(bool)
{
}
