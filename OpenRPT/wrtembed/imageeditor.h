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

#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <QDialog>

#include "ui_imageeditor.h"

class ImageEditor : public QDialog, public Ui::ImageEditor
{
    Q_OBJECT

public:
    ImageEditor(QWidget* parent = 0, Qt::WFlags fl = 0);
    ~ImageEditor();

public slots:
    virtual void cbStatic_toggled(bool yes);
    virtual QString getImageData();
    virtual void setImageData(QString dat);
    virtual QString getMode();
    virtual bool isInline();
    virtual void setMode(QString m);
    virtual void setInline(bool yes);
    virtual void btnLoad_clicked();

protected:
    QString uudata;

protected slots:
    virtual void languageChange();

};

#endif // IMAGEEDITOR_H
