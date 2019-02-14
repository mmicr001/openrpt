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

#include <QVariant>
#include <QPushButton>
#include <QComboBox>

#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
#include <QDebug>

FindDialog::FindDialog(QWidget* parent)
    : QDialog(parent)
{
  setupUi(this);

  _lbWarning->setVisible(false);
  connect(_btnFind,     SIGNAL(clicked()),           this,   SLOT(sFind()));
  connect(_leSearch,    SIGNAL(returnPressed()),     this,   SLOT(sFind()));
  connect(_btnClose,    SIGNAL(clicked()),           this,   SLOT(sClose()));
}


FindDialog::~FindDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

void FindDialog::languageChange()
{
  retranslateUi(this);
}

void FindDialog::setTextEdit(QTextEdit* t)
{
  _text = t;
}

void FindDialog::setWarningVisible(bool value)
{
  return _lbWarning->setVisible(value);
}

void FindDialog::sClose()
{
  reject();
}



int i=0;
void FindDialog::sFind()
{
  qDebug() << "find " << i++; 
  if (_lbWarning->isVisible())
  {
    setWarningVisible(false);
    sMoveCursorToStart();
  }
  
  QString term = _leSearch->text();
  if(!_text->find(term))
    setWarningVisible(true);    
}

void FindDialog::sMoveCursorToStart()
{
  QTextCursor c = _text->textCursor();
  c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor,1);
  _text->setTextCursor(c);
}