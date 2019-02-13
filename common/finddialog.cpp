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

#include "finddialog.h"

#include <QTextEdit>

FindDialog::FindDialog(QWidget* parent)
    : QDialog(parent),
      _text(0)
{
  setupUi(this);

  _lbWarning->setVisible(false);
  connect(_btnFind,     SIGNAL(clicked()),           this->parent(),   SLOT(sFind()));
  connect(_leSearch,    SIGNAL(editingFinished()),   this->parent(),   SLOT(sFind()));
  connect(_btnClose,    SIGNAL(clicked()),           this,             SLOT(sClose()));
}

FindDialog::~FindDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

void FindDialog::languageChange()
{
  retranslateUi(this);
}

QString FindDialog::getSearchTerm()
{
  return _leSearch->text();
}

void FindDialog::setWarningVisible(bool value)
{
  return _lbWarning->setVisible(value);
}

void FindDialog::sClose()
{
  reject();
}

void FindDialog::sFind()
{
  setWarningVisible(false);
  if (! _text->find(getSearchTerm()))
    setWarningVisible(true);
}

void FindDialog::setTextEdit(QTextEdit *pText)
{
  _text = pText;
}

QTextEdit *FindDialog::textEdit()
{
  return _text;
}
