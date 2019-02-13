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

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QString>

#include "tmp/ui_finddialog.h"

class QTextEdit;

class FindDialog : public QDialog, public Ui::Find
{
    Q_OBJECT

public:
    FindDialog(QWidget* parent = 0);
    ~FindDialog();


public slots:
  void languageChange();
  QString getSearchTerm();
  void setWarningVisible(bool set);
  void sClose();
  void sFind();
  void setTextEdit(QTextEdit *pText);
  QTextEdit *textEdit();

protected slots:
    
protected:
  QTextEdit *_text;

};

#endif // FINDDIALOG_H
