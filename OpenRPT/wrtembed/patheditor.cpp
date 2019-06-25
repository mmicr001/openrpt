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

#include "patheditor.h"

#include <QColorDialog>
#include <QValidator>
#include <QVariant>

PathEditor::PathEditor(QWidget* parent, QPen initPen, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setupUi(this);

  _pen = initPen;
  _sbWidth->setValue(_pen.width());
  switch(_pen.style())
  {
    case Qt::DotLine:
      _rbDottedStyle->setChecked(true);
    break;
    case Qt::DashLine:
      _rbDashedStyle->setChecked(true);
    break;
    default:
      _rbSolidStyle->setChecked(true);
  }

  // signals and slots connections
  connect(_btnAccept, SIGNAL(clicked()), this, SLOT(accept()));
  connect(_btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
  connect(_btnColor, SIGNAL(clicked()), this, SLOT(_btnColor_clicked()));

}

PathEditor::~PathEditor()
{
}

void PathEditor::languageChange()
{
  retranslateUi(this);
}

void PathEditor::_btnColor_clicked()
{
  QColor col = QColorDialog::getColor(_pen.color(), this);
  if(col.isValid()) {
    _pen.setColor(col);
  }
}

void PathEditor::accept()
{
  _pen.setWidth(_sbWidth->value());

  if(_rbDottedStyle->isChecked())
    _pen.setStyle(Qt::DotLine);
  else if (_rbDashedStyle->isChecked())
    _pen.setStyle(Qt::DashLine);
  else
    _pen.setStyle(Qt::SolidLine);

  QDialog::accept();
}

