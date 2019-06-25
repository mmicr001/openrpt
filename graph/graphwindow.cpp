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

#include "graphwindow.h"

#include <QSqlQuery>

GraphWindow::GraphWindow(QWidget* parent, Qt::WindowFlags fl)
    : QMainWindow(parent, fl)
{
    setupUi(this);

    (void)statusBar();

    // signals and slots connections
    connect(_hPadSpinbox, SIGNAL(valueChanged(int)), _graph, SLOT(setHPadding(int)));
    connect(_vPadSpinbox, SIGNAL(valueChanged(int)), _graph, SLOT(setVPadding(int)));
    connect(_titleEdit, SIGNAL(textChanged(const QString&)), _graph, SLOT(setTitle(const QString&)));
    connect(_dataEdit, SIGNAL(textChanged(const QString&)), _graph, SLOT(setDataLabel(const QString&)));
    connect(_valueEdit, SIGNAL(textChanged(const QString&)), _graph, SLOT(setValueLabel(const QString&)));
    connect(_maxValueSpinbox, SIGNAL(valueChanged(int)), _graph, SLOT(setMaxValue(int)));
    connect(_minValueSpinbox, SIGNAL(valueChanged(int)), _graph, SLOT(setMinValue(int)));
    connect(_numSetSpinbox, SIGNAL(valueChanged(int)), this, SLOT(setColCount(int)));
    connect(_numRefSpinbox, SIGNAL(valueChanged(int)), this, SLOT(setRowCount(int)));
    connect(_dataTable, SIGNAL(cellChanged(int,int)), this, SLOT(_dataTable_valueChanged(int,int)));
    connect(_labelTable, SIGNAL(cellChanged(int,int)), this, SLOT(_labelTable_valueChanged(int,int)));
    connect(_cbBars, SIGNAL(toggled(bool)), _graph, SLOT(setDrawBars(bool)));
    connect(_cbLines, SIGNAL(toggled(bool)), _graph, SLOT(setDrawLines(bool)));
    connect(_cbPoints, SIGNAL(toggled(bool)), _graph, SLOT(setDrawPoints(bool)));
    connect(_btnClear, SIGNAL(clicked()), this, SLOT(_btnClear_clicked()));
    connect(_btnSql, SIGNAL(clicked()), this, SLOT(_btnSql_clicked()));
}

GraphWindow::~GraphWindow()
{
    // no need to delete child widgets, Qt does it all for us
}

void GraphWindow::languageChange()
{
    retranslateUi(this);
}

void GraphWindow::setColCount(int cnt)
{
  _dataTable->setColumnCount(cnt);
}

void GraphWindow::setRowCount(int cnt)
{
  _dataTable->setRowCount(cnt);
  _labelTable->setRowCount(cnt);
}

void GraphWindow::_dataTable_valueChanged( int r, int s)
{
    if(!_noUpdate)
        _graph->setSetValue(r, s, _dataTable->item(r, s)->text().toDouble());
}

void GraphWindow::_labelTable_valueChanged( int r, int s)
{
    if(!_noUpdate)
        _graph->setReferenceLabel(r, _labelTable->item(r, s)->text());
}

void GraphWindow::_btnClear_clicked()
{
    _noUpdate = true;
    for(int r = 0; r < _labelTable->rowCount(); r++) {
        _labelTable->item(r, 0)->setText(QString::null);
        for(int c = 0; c < _dataTable->columnCount(); c++) {
            _dataTable->item(r, c)->setText(QString::null);
        }
    }
    _graph->clear();
    _noUpdate = false;
}

void GraphWindow::init(bool haveDB)
{
    _noUpdate = false;
    _gbSql->setEnabled(haveDB);
}

void GraphWindow::_btnSql_clicked()
{
    _noUpdate = true;
    _btnClear_clicked();
    QString sql = _editSql->toPlainText();
    QSqlQuery qry = QSqlQuery(sql);
    _graph->populateFromResult(qry);
    _noUpdate = false;
}
