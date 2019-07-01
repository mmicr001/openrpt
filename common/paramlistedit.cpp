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

#include "paramlistedit.h"

#include <QVariant>

ParamListEdit::ParamListEdit(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);

    // signals and slots connections
    connect(_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(_select, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_list, SIGNAL(itemSelectionChanged()), this, SLOT(sSelectionChanged()));
}

ParamListEdit::~ParamListEdit()
{
    // no need to delete child widgets, Qt does it all for us
}

void ParamListEdit::languageChange()
{
    retranslateUi(this);
}

void ParamListEdit::sSelectionChanged()
{
  _select->setEnabled(_list->currentRow()!=-1);
}

