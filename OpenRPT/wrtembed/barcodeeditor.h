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

#ifndef BARCODEEDITOR_H
#define BARCODEEDITOR_H

#include <QDialog>
#include <QGridLayout>
#include <QString>

#include "ui_barcodeeditor.h"

#include "dbarcodeconfig.h"
#include "dmatrixrectconfig.h"
#include "dmatrixsquareconfig.h"
#include "pdf417config.h"
#include "qrconfig.h"

class BarcodeEditor : public QDialog, public Ui::BarcodeEditor
{
    Q_OBJECT

public:
    BarcodeEditor(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~BarcodeEditor();

    QString format();
    void setCBSliderMaxValue(int value);
    int getCBSlideMaxValue();

    void setDatamatrixEditor(QString format);
    void setPDF417Editor(QString format);
    void setQREditor(QString format);

public slots:
    virtual void cbFormat_activated(int);
    virtual void sliderMaxVal_sliderMoved(int);
    void cbFormat_ViewConfig(int);

protected slots:
    virtual void languageChange();

protected:
    void closeEvent(QCloseEvent *);

private:
    DMatrixSquareConfig* dMatrixSquare;
    DMatrixRectConfig* dMatrixRect;
    DBarcodeConfig* dBarcode;
    PDF417Config* pdf417conf;
    QRConfig* qrconf;

    int iDatamatrix_square;
    int iDatamatrix_rect;
    int iPDF417;
    int iQR;
};

#endif // BARCODEEDITOR_H
