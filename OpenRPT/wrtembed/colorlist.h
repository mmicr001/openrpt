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

#ifndef COLORLIST_H
#define COLORLIST_H

#include <QDialog>

#include "ui_colorlist.h"

class ColorList : public QDialog, public Ui::ColorList
{
    Q_OBJECT

public:
    ColorList(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~ColorList();

public slots:
    virtual void _btnAdd_clicked();
    virtual void _lbColors_dblClick( QListWidgetItem * item );
    virtual void _btnEdit_clicked();
    virtual void _btnDelete_clicked();
    virtual void init( QMap<QString, QColor> * cmap );
    virtual void sEnableButtons();

protected:
    QMap<QString, QColor>* _colorMap;

protected slots:
    virtual void languageChange();

};

#endif // COLORLIST_H
