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

#include "colorlist.h"
#include "coloreditor.h"

#include <QVariant>
#include <QMessageBox>

ColorList::ColorList(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);


    // signals and slots connections
    connect(_btnClose, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_btnAdd, SIGNAL(clicked()), this, SLOT(_btnAdd_clicked()));
    connect(_btnEdit, SIGNAL(clicked()), this, SLOT(_btnEdit_clicked()));
    connect(_btnDelete, SIGNAL(clicked()), this, SLOT(_btnDelete_clicked()));
    connect(_lbColors, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(_lbColors_dblClick(QListWidgetItem*)));
    connect(_lbColors, SIGNAL(itemSelectionChanged()), this, SLOT(sEnableButtons()));

    _btnEdit->setEnabled(false);
    _btnDelete->setEnabled(false);
}

ColorList::~ColorList()
{
    // no need to delete child widgets, Qt does it all for us
}

void ColorList::languageChange()
{
    retranslateUi(this);
}

void ColorList::_btnAdd_clicked()
{
    if(!_colorMap) {
        QMessageBox::critical(this, tr("Error"),tr("This dialog was not properly setup and cannot perform the requested action!"),1,0,0);
        return;
    }
    ColorEditor ce(this);

    bool exitLoop = false;
    while (!exitLoop)
    {
        if(ce.exec() == QDialog::Accepted) {
            QString name = ce.getColorName();
            QColor color = ce.getColor();

            if(name.length() < 1) {
                QMessageBox::warning(this, tr("Warning"),
                    tr("No color name was specified!\nPlease specify a name for this color."), 1, 0, 0);
            }
	        else if(_colorMap->contains(name)) {
                QMessageBox::warning(this, tr("Warning"),
                    tr("The color name you specified is already in use!\nPlease specify a UNIQUE name for this color."), 1, 0, 0);
            }
            else
            {
              _colorMap->insert(name, color);
              _lbColors->addItem(name);
              exitLoop = true;
            }
        } else {
            exitLoop = true;
        }
    }
}

void ColorList::_lbColors_dblClick( QListWidgetItem * item )
{
    if(!_colorMap) {
        QMessageBox::critical(this, tr("Error"),tr("This dialog was not properly setup and cannot perform the requested action!"),1,0,0);
        return;
    }
    if(item != 0) {
        QString name = item->text();
        ColorEditor ce(this);
        ce.setColorName(name);
        ce.setColor((*_colorMap)[name]);
        bool exitLoop = false;
        while(!exitLoop) {
            if(ce.exec() == QDialog::Accepted) {
                QString new_name = ce.getColorName();
                QColor  new_color = ce.getColor();

                if(new_name.length() < 1) {
                    QMessageBox::warning(this, tr("Warning"),
                        tr("No color name was specified!\nPlease specify a name for this color."), 1, 0, 0);
                }
                else if(new_name != name && _colorMap->contains(new_name)) {
                    QMessageBox::warning(this, tr("Warning"),
                        tr("The color name you specified is already in use!\nPlease specify a UNIQUE name for this color."), 1, 0, 0);
                }
                else
                {
                    if(new_name != name) {
                        _colorMap->remove(name);
                        item->setText(new_name);
                        name = new_name;
                    }

                    _colorMap->insert(name, new_color);

                    exitLoop = true;
                }
            } else {
                exitLoop = true;
            }
        }
    }
}

void ColorList::_btnEdit_clicked()
{
    _lbColors_dblClick(_lbColors->currentItem());
}

void ColorList::_btnDelete_clicked()
{
    if(!_colorMap) {
        QMessageBox::critical(this, tr("Error"),tr("This dialog was not properly setup and cannot perform the requested action!"),1,0,0);
        return;
    }

    int citem = _lbColors->currentRow();
    if(citem != -1) {
        QString name = _lbColors->item(citem)->text();
        _colorMap->remove(name);
        _lbColors->takeItem(citem);
    }
}


void ColorList::init( QMap<QString, QColor> * cmap)
{
    _colorMap = cmap;

    QMapIterator<QString, QColor> cit(*_colorMap);
    while(cit.hasNext())
    {
        cit.next();
        _lbColors->addItem(cit.key());
    }
}

void ColorList::sEnableButtons()
{
  _btnEdit->setEnabled(!_lbColors->selectedItems().isEmpty());
  _btnDelete->setEnabled(!_lbColors->selectedItems().isEmpty());
}
