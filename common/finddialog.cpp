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

#include "finddialog.h"

#include <QVariant>
#include <QPushButton>
#include <QComboBox>

FindDialog::FindDialog(QWidget* parent)
    : QDialog(parent)
{
  setupUi(this);

  connect(_btnNext,     SIGNAL(clicked()),                   this,   SLOT(sFind()));
  connect(_btnPrev,     SIGNAL(clicked()),                   this,   SLOT(sFindPrev()));
  connect(_leSearch,    SIGNAL(textChanged(const QString&)), this,   SLOT(sSearchChanged()));
  connect(_btnClose,    SIGNAL(clicked()),                   this,   SLOT(reject()));
  connect(_cbMatchCase, SIGNAL(clicked()),                   this,   SLOT(sSearchChanged()));
  connect(_cbMatchWord, SIGNAL(clicked()),                   this,   SLOT(sSearchChanged()));
  connect(_cbRegex,     SIGNAL(clicked()),                   this,   SLOT(sSearchChanged()));

  _lbWarning->setVisible(false);
  _searchChanged=false;
}


FindDialog::~FindDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

void FindDialog::languageChange()
{
  retranslateUi(this);
}

void FindDialog::show()
{
  QDialog::show();
  _leSearch->setFocus(); //allow user to start typing without clicking on the lineedit
}

void FindDialog::setTextEdit(QTextEdit* t)
{
  _text = t;
  _leSearch->setText(_text->textCursor().selectedText()); //populate search lineedit if user has highlighted text
  backgroundColor = _text->palette().color(QPalette::Base); 
}

void FindDialog::sCountMatches()
{
  int currCursorPos = _text->textCursor().position();
  bool direction = _reverseSearch;
  cursors.clear();

  //do forward search from the top of the doc
  _reverseSearch = false;  sSetFlags();
  sMoveCursorTo(0);
 
  if(_cbRegex->isChecked())
  {
    QRegExp term = QRegExp(_leSearch->text());
    while(_text->find(term,flags))
    {
      _matches.append(_text->textCursor().position());
      cursors.append(_text->textCursor());
    }
  }
  else
  {
    QString term = _leSearch->text();
    while(_text->find(term,flags))
    {
      _matches.append(_text->textCursor().position());
      cursors.append(_text->textCursor());
    }
  }
  
  sMoveCursorTo(currCursorPos); // put cursor back where it was
  _reverseSearch = direction;   // return search direction to what it was
  _searchChanged=false;
  highlightMatches(QColor("yellow"));
}

void FindDialog::sFindPrev()
{
  _reverseSearch = true;
  sFind();
  _reverseSearch = false;
}

void FindDialog::sFind()
{
  sSetWarning(false);
  sSetFlags();
  _leSearch->setStyleSheet( QString( "background-color: white"));

  if(_searchChanged)
    sCountMatches();
  
  if(!_matches.count())
  {
    _leSearch->setStyleSheet( QString( "background-color: red"));
    _lbCount->setText("No matches");
    return;
  }

  /* There is a special case in which backwards search skips matches. This is seen in: 
  https://bugreports.qt.io/browse/QTBUG-48035
  This seems like a rare case to fall into */
  
  bool found = false;
  if(_cbRegex->isChecked())
  {
    QRegExp term = QRegExp(_leSearch->text());
    found = _text->find(term,flags);  
  }
  else
  {
    QString term = _leSearch->text();
    found = _text->find(term,flags);
  }

  if(!found)
  {
    sSetWarning(true);
    if(_cbWrapAround->isChecked())
    {
      if(!_reverseSearch)
        sMoveCursorTo(0);
      else
        sMoveCursorTo(_text->document()->characterCount()-1);
    }
  }
  
  // update counter on dialog label
  if(_matches.contains(_text->textCursor().position()))
  {
    int current = _matches.indexOf(_text->textCursor().position())+1; 
    QString count = tr("Match  %1  of %2").arg(current).arg(_matches.count());
    _lbCount->setText(count);
  }

  _leSearch->selectAll();
}

void FindDialog::sMoveCursorTo(int pos)
{
  QTextCursor c = _text->textCursor();
  c.setPosition(pos, QTextCursor::MoveAnchor);  // QTextEdit::moveCursor() was considered but limits us to specific move operations, and not any position on the document
  _text->setTextCursor(c);
}

void FindDialog::sSetFlags()
{
  flags = 0;
  if(_cbMatchCase->isChecked())
    flags = flags | QTextDocument::FindCaseSensitively;
  if(_cbMatchWord->isChecked())
    flags = flags | QTextDocument::FindWholeWords;
  if(_reverseSearch)
    flags = flags | QTextDocument::FindBackward;
}

void FindDialog::sSetWarning(bool set)
{
  _lbWarning->setVisible(set);
}

void FindDialog::sSearchChanged()
{
  _searchChanged = true;
  _matches.clear();
  _lbCount->clear();
  _leSearch->setStyleSheet( QString( "background-color: white"));

  highlightMatches(backgroundColor);
  //update search paramters
  sSetFlags();

  //save checkboxes
  bool _matchCase  = _cbMatchCase->isChecked();
  bool _matchWord  = _cbMatchWord->isChecked();
  bool _regex      = _cbRegex->isChecked();
  bool _wrapAround = _cbWrapAround->isChecked();
}

void FindDialog::highlightMatches(QColor color)
{
  foreach(QTextCursor c,cursors)
  {
    QTextCharFormat tfc;
    tfc.setBackground(QBrush(color));
    c.setCharFormat(tfc);
  }
}
