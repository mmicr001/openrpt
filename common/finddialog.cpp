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

FindDialog::FindDialog(QWidget* parent)
    : QDialog(parent)
{
  setupUi(this);

  _lbWarning->setVisible(false);
  connect(_btnNext,     SIGNAL(clicked()),           this,   SLOT(sFind()));
  connect(_btnPrev,     SIGNAL(clicked()),           this,   SLOT(sFindPrev()));
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
  _leSearch->setText(_text->textCursor().selectedText()); //populate search lineedit if user has highlighted text
}

void FindDialog::sClose()
{
  reject();
}

void FindDialog::sFindPrev()
{
  sFind(true);
}
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
void FindDialog::sFind(bool backwards)
{
  sSetWarning();
  _leSearch->setStyleSheet( QString( "background-color: white"));
  // determine flags
  QTextDocument::FindFlags flags ;
  if(_cbMatchCase->isChecked())
    flags = flags | QTextDocument::FindCaseSensitively;
  if(_cbMatchWord->isChecked())
    flags = flags | QTextDocument::FindWholeWords;
  if(backwards)
    flags = flags | QTextDocument::FindBackward;
  
  if(_cbRegex->isChecked())
  {
    QRegExp term = QRegExp(_leSearch->text());
    if(!_text->find(term,flags))
      _leSearch->setStyleSheet( QString( "background-color: red"));
  }
  else
  {
    QString term = _leSearch->text();
     if(!_text->find(term,flags))
     {
       _leSearch->setStyleSheet( QString( "background-color: red"));
     }
  }  
  if( _text->textCursor().atEnd())
  {
    sSetWarning(true);
    if(_cbWrapAround->isChecked())
      sMoveCursorToStart();
  }
     
     
}

void FindDialog::sMoveCursorToStart()
{
  QTextCursor c = _text->textCursor();
  c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor,1);
  _text->setTextCursor(c);
}

void FindDialog::sSetWarning(bool set)
{
  _lbWarning->setVisible(set);
}