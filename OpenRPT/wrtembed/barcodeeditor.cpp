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

#include "barcodeeditor.h"
#include "barcodes.h"

#include <QVariant>
#include <QValidator>
#include <QRegExp>
#include <QDebug>
#if QT_VERSION >= 0x050000
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#endif

BarcodeEditor::BarcodeEditor(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);

    this->dBarcode = new DBarcodeConfig(this);
    this->dBarcode->setVisible(false);

    this->dMatrixRect = new DMatrixRectConfig(this);
    this->dMatrixRect->setVisible(false);

    this->dMatrixSquare = new DMatrixSquareConfig(this);
    this->dMatrixSquare->setVisible(false);

    this->pdf417conf = new PDF417Config(this);
    this->pdf417conf->setVisible(false);

    this->qrconf = new QRConfig(this);
    this->qrconf->setVisible(false);

    //this->cbFormat_ViewConfig(0);
    // signals and slots connections
    connect(cbFormat,       SIGNAL(triggered(int)),     this,               SLOT(cbFormat_activated(int)));
    connect(cbFormat,       SIGNAL(triggered(int)),     this,               SLOT(cbFormat_ViewConfig(int)));
//    connect(sliderMaxVal,   SIGNAL(valueChanged(int)),  labelMaxVal,    SLOT(setNum(int)));
//    connect(sliderMaxVal,   SIGNAL(sliderMoved(int)),   this,           SLOT(sliderMaxVal_sliderMoved(int)));
    connect(buttonOk,       SIGNAL(clicked()),          this,               SLOT(accept()));
    connect(buttonCancel,   SIGNAL(clicked()),          this,               SLOT(reject()));

    connect(buttonOk,       SIGNAL(clicked()),          this->dMatrixRect,  SLOT(setVisible2()));
    connect(buttonCancel,   SIGNAL(clicked()),          this->dMatrixRect,  SLOT(setVisible2()));
    connect(buttonCancel,   SIGNAL(clicked()),          this->dMatrixSquare,SLOT(setVisible2()));
    connect(buttonOk,       SIGNAL(clicked()),          this->dMatrixSquare,SLOT(setVisible2()));

    leXPos->setValidator(new QDoubleValidator(0.0,100.0,3,leXPos));
    leYPos->setValidator(new QDoubleValidator(0.0,100.0,3,leYPos));
    
    leWidth->setValidator(new QDoubleValidator(0.01,100.0,3,leWidth));
    leHeight->setValidator(new QDoubleValidator(0.01,100.0,3,leHeight));
    leNarrowBarWidth->setValidator(new QDoubleValidator(0.005,0.1,3,leNarrowBarWidth));

    iDatamatrix_square = cbFormat->findText(tr("Datamatrix square"));
    iDatamatrix_rect = cbFormat->findText(tr("Datamatrix rectangle"));
    iPDF417 = cbFormat->findText(tr("PDF417"));
    iQR = cbFormat->findText(tr("QR"));
}

BarcodeEditor::~BarcodeEditor()
{
    // no need to delete child widgets, Qt does it all for us
    delete this->dBarcode;
    delete this->dMatrixRect;
    delete this->dMatrixSquare;
    delete this->pdf417conf;
    delete this->qrconf;
}

void BarcodeEditor::languageChange()
{
    retranslateUi(this);
}

void BarcodeEditor::cbFormat_activated(int)
{
    // the format was changed so we need to recalculate our minimum sizes
}

void BarcodeEditor::sliderMaxVal_sliderMoved( int )
{
    // the slider for the max value length has been changed so we need to recalculate the minimum sizes
}

QString BarcodeEditor::format()
{
    //the alignement is Center
    QString qsAlign = "_C";

    if(this->rbAlignLeft->isChecked())
    {
        qsAlign = "_L";
    }
    if(this->rbAlignRight->isChecked())
    {
        qsAlign = "_R";
    }


    if(this->cbFormat->currentIndex() == iPDF417)
    {
        return this->pdf417conf->format(qsAlign);
    }
    if(this->cbFormat->currentIndex() == iQR)
    {
        return this->qrconf->format(qsAlign);
    }
    else if(this->cbFormat->currentIndex() == iDatamatrix_square)
    {
        return this->dMatrixSquare->format() + qsAlign;
    }
    else if(this->cbFormat->currentIndex() == iDatamatrix_rect)
    {
        return this->dMatrixRect->format() + qsAlign;
    }
    else
    {
        return this->cbFormat->currentText();
    }

}

void BarcodeEditor::cbFormat_ViewConfig(int i)
{
    if(i==iDatamatrix_square)
    {
        this->leNarrowBarWidth->setVisible(false);
        this->lnarrowBar->setVisible(false);

        this->_princpalLayout->insertWidget(1,this->dMatrixSquare);
        this->dMatrixSquare->setVisible(true);
        this->dMatrixRect->setVisible2(false);
        this->dBarcode->setVisible(false);
        this->pdf417conf->setVisible(false);
        this->qrconf->setVisible(false);
    }
    else if(i==iDatamatrix_rect)
    {
        this->leNarrowBarWidth->setVisible(false);
        this->lnarrowBar->setVisible(false);

        this->_princpalLayout->insertWidget(1,this->dMatrixRect);
        this->dMatrixSquare->setVisible2(false);
        this->dMatrixRect->setVisible(true);
        this->dBarcode->setVisible(false);
        this->pdf417conf->setVisible(false);
        this->qrconf->setVisible(false);
     }
     else if (i==iPDF417)
     {
        this->leNarrowBarWidth->setVisible(false);
        this->lnarrowBar->setVisible(false);

        this->_princpalLayout->insertWidget(1,this->pdf417conf);
        this->dMatrixSquare->setVisible2(false);
        this->dMatrixRect->setVisible(false);
        this->dBarcode->setVisible(false);
        this->pdf417conf->setVisible(true);
        this->qrconf->setVisible(false);
     }
     else if (i ==iQR)
     {
        this->leNarrowBarWidth->setVisible(false);
        this->lnarrowBar->setVisible(false);

        this->_princpalLayout->insertWidget(1,this->qrconf);
        this->dMatrixSquare->setVisible2(false);
        this->dMatrixRect->setVisible(false);
        this->dBarcode->setVisible(false);
        this->pdf417conf->setVisible(false);
        this->qrconf->setVisible(true);
     }
     else
     {
        this->leNarrowBarWidth->setVisible(true);
        this->lnarrowBar->setVisible(true);

        this->_princpalLayout->insertWidget(1,this->dBarcode);
        this->dMatrixSquare->setVisible2(false);
        this->dMatrixRect->setVisible2(false);
        this->dBarcode->setVisible(true);
        this->pdf417conf->setVisible(false);
        this->qrconf->setVisible(false);
    }
}

int BarcodeEditor::getCBSlideMaxValue()
{
    return this->dBarcode->getSliderMaxValue();
}

void BarcodeEditor::setCBSliderMaxValue(int value)
{
    this->dBarcode->setSliderMaxValue(value);
}

void BarcodeEditor::closeEvent(QCloseEvent *)
{
    this->dMatrixRect->setVisible2(false);
    this->dMatrixSquare->setVisible2(false);
    this->dMatrixRect->close();
    this->dMatrixSquare->close();
    this->pdf417conf->close();
    this->qrconf->close();
}

void BarcodeEditor::setDatamatrixEditor(QString format)
{
    DmtxInfos dmtxInfos = extractInfosDtmx(format);

    if(dmtxInfos.type <24)
    {
        this->cbFormat->setCurrentIndex(iDatamatrix_square);
        this->dMatrixSquare->setCursorValue(dmtxInfos.type);
        this->cbFormat_ViewConfig(iDatamatrix_square);
    }
    else
    {
      this->cbFormat->setCurrentIndex(iDatamatrix_rect);
        this->dMatrixRect->setIndexValue(dmtxInfos.type - 24);
        this->cbFormat_ViewConfig(iDatamatrix_rect);
    }

    if(dmtxInfos.align == "L")
        this->rbAlignLeft->setChecked(true);
    if(dmtxInfos.align == "C")
        this->rbAlignCenter->setChecked(true);
    if(dmtxInfos.align == "R")
        this->rbAlignRight->setChecked(true);
}

void BarcodeEditor::setPDF417Editor(QString format)
{
    #if QT_VERSION >= 0x050000
    QByteArray ba = QByteArray(format.toStdString().c_str(), format.toStdString().length());
    QJsonDocument doc = QJsonDocument::fromJson(ba);
    QJsonObject obj = doc.object();
    QJsonValue codewords = obj.value("codewords");
    QJsonValue columns = obj.value("columns");
    QJsonValue errorCorrection = obj.value("errorCorrection");
    QJsonValue alignment = obj.value("alignment");

    this->pdf417conf->setCodewords(codewords.toInt());
    this->pdf417conf->setColumns(columns.toInt());
    this->pdf417conf->setErrorCorrecton(errorCorrection.toInt());

    if(alignment.toString() == "_L")
        this->rbAlignLeft->setChecked(true);
    if(alignment.toString() == "_C")
        this->rbAlignCenter->setChecked(true);
    if(alignment.toString() == "_R")
        this->rbAlignRight->setChecked(true);
    #endif
}

void BarcodeEditor::setQREditor(QString format)
{
    #if QT_VERSION >= 0x050000
    QByteArray ba = QByteArray(format.toStdString().c_str(), format.toStdString().length());
    QJsonDocument doc = QJsonDocument::fromJson(ba);
    QJsonObject obj = doc.object();
    QJsonValue size = obj.value("size");
    QJsonValue autosize = obj.value("autosize");
    QJsonValue errorCorrection = obj.value("errorCorrection");
    QJsonValue alignment = obj.value("alignment");

    this->qrconf->setQRSize(size.toInt());

    // trying to figure out why toBool() never worked killed 45 minutes
    // so here we are
    if (autosize.toString() == "true") {
        this->qrconf->setAutoSize(true);
    }
    this->qrconf->setErrorCorrection(errorCorrection.toInt());

    if(alignment.toString() == "_L")
        this->rbAlignLeft->setChecked(true);
    if(alignment.toString() == "_C")
        this->rbAlignCenter->setChecked(true);
    if(alignment.toString() == "_R")
        this->rbAlignRight->setChecked(true);
    #endif
}
