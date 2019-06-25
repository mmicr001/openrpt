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

#include "coloreditor.h"

#include <QVariant>
#include <QColorDialog>
#include <QValidator>

ColorEditor::ColorEditor(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);


    // signals and slots connections
    connect(_btnAccept, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(_btnColor, SIGNAL(clicked()), this, SLOT(_btnColor_clicked()));

    QIntValidator * intv = new QIntValidator(0, 255, this);
    _editRed->setValidator(intv);
    _editRed->setText(tr("0"));
    _editGreen->setValidator(intv);
    _editGreen->setText(tr("0"));
    _editBlue->setValidator(intv);
    _editBlue->setText(tr("0"));
}

ColorEditor::~ColorEditor()
{
    // no need to delete child widgets, Qt does it all for us
}

void ColorEditor::languageChange()
{
    retranslateUi(this);
}

void ColorEditor::_btnColor_clicked()
{
    QColor col = QColorDialog::getColor(getColor(), this);
    if(col.isValid()) {
	setColor(col);
    }
}

void ColorEditor::setColorName( QString name )
{
    _editName->setText(name);
}

void ColorEditor::setColor( const QColor & col )
{
    _editRed->setText(QString::number(col.red()));
    _editGreen->setText(QString::number(col.green()));
    _editBlue->setText(QString::number(col.blue()));
}

QColor ColorEditor::getColor()
{
    return QColor(_editRed->text().toInt(),
	            _editGreen->text().toInt(),
	            _editBlue->text().toInt());
}

QString ColorEditor::getColorName()
{
    return _editName->text();
}
