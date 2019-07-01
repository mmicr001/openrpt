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

#include "editpreferences.h"

#include <QVariant>
#include <QValidator>
#include <QFontDialog>
#include "data.h"

EditPreferences::EditPreferences(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);


    // signals and slots connections
    connect(_btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(_btnOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cbGridSymetrical, SIGNAL(toggled(bool)), _lblGridSizeY, SLOT(setDisabled(bool)));
    connect(_cbGridSymetrical, SIGNAL(toggled(bool)), _leGridSizeY, SLOT(setDisabled(bool)));
    connect(_btnChangeFont, SIGNAL(clicked()), this, SLOT(changeDefaultFont()));
    connect(_cbLanguage, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(selLanguage(const QString &)));

    // install validator on _leGridSizeX and _leGridSizeY
    QDoubleValidator * dblval = new QDoubleValidator(0.01, 1000, 2, this);
    _leGridSizeX->setValidator(dblval);
    _leGridSizeY->setValidator(dblval);
    _cbLanguage->addItems(OpenRPT::languages.languageTitlesList());
    for (int i=0; i<_cbLanguage->count(); i++)
    {
        if(_cbLanguage->itemText(i)==OpenRPT::languages.selectedTitle()) {
            _cbLanguage->setCurrentIndex(i);
            break;
        }
    }

    //initialize combobox
    _cbPageSize->clear();
    _cbPageSize->addItem(tr("Letter"), "Letter");
    _cbPageSize->addItem(tr("Legal"), "Legal");
    _cbPageSize->addItem(tr("A4"), "A4");
    _cbPageSize->addItem(tr("Custom"), "Custom");
    _cbPageSize->addItem(tr("Label"), "Label");

    _rbPortrait->setChecked(false);
    _rbLandscape->setChecked(false);
}

EditPreferences::~EditPreferences()
{
    // no need to delete child widgets, Qt does it all for us
}

void EditPreferences::languageChange()
{
    retranslateUi(this);
}


void EditPreferences::changeDefaultFont()
{
    bool valid = false;
    QFont fnt = QFontDialog::getFont(&valid, _leDefaultFont->font(), this);
    if(valid) {
	setDefaultFont(fnt);
    }
}


void EditPreferences::setGridSize( double x, double y )
{
    if(x < 0.01) x = 0.01;
    if(x > 1000) x = 1000;
    if(y < 0.01) y = 0.01;
    if(y > 1000) y = 1000;
    QString sx = QString::number(x, 'g', 2);
    QString sy = QString::number(y, 'g', 2);
    _leGridSizeX->setText(sx);
    _leGridSizeY->setText(sy);
    if(sx == sy) {
	_cbGridSymetrical->setChecked(true);
    }
}


double EditPreferences::gridSizeX()
{
    bool valid = false;
    double dbl = _leGridSizeX->text().toDouble(&valid);
    if(!valid) {
	dbl = 0.01;
    }
    return dbl;
}


double EditPreferences::gridSizeY()
{
    if(_cbGridSymetrical->isChecked()) {
	return gridSizeX();
    }
    bool valid = false;
    double dbl = _leGridSizeY->text().toDouble(&valid);
    if(!valid) {
	dbl = 0.01;
    }
    return dbl;
}


bool EditPreferences::showGrid()
{
    return _cbShowGrid->isChecked();
}


bool EditPreferences::snapGrid()
{
    return _cbSnapGrid->isChecked();
}


void EditPreferences::setShowGrid( bool show )
{
    _cbShowGrid->setChecked(show);
}


void EditPreferences::setSnapGrid( bool snap )
{
    _cbSnapGrid->setChecked(snap);
}


void EditPreferences::setDefaultFont( QFont fnt )
{
    _leDefaultFont->setText(fnt.family());
    _leDefaultFont->setFont(fnt);
}


QFont EditPreferences::defaultFont()
{
    return _leDefaultFont->font();
}

void EditPreferences::selLanguage( QString sel )
{
    _selectedLanguage = sel;
}

void EditPreferences::setPageSize(QString ps)
{
   _cbPageSize->setCurrentText(ps);
}

void  EditPreferences::setPageOrientation(QString po)
{
  if(po=="portrait")
    _rbPortrait->setChecked(true);
  else
    _rbLandscape->setChecked(true);
}

