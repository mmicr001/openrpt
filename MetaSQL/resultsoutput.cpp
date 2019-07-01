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

#include "resultsoutput.h"

#include <QClipboard>
#include <QMenu>
#include <QTableWidgetItem>

#define DEBUG false

ResultsOutput::ResultsOutput(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setupUi(this);

  connect(_table, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(createContextMenu(const QPoint &)));

  _menu = new QMenu(this);
  _copyAction = _menu->addAction(tr("Copy All"), this, SLOT(copy()));
}

ResultsOutput::~ResultsOutput()
{
    // no need to delete child widgets, Qt does it all for us
}

void ResultsOutput::languageChange()
{
    retranslateUi(this);
}

void ResultsOutput::copy()
{
  if (DEBUG)
    qDebug("ResultsOutput::copy() entered");

  QClipboard *clipboard = QApplication::clipboard();
  QAbstractItemModel *model = _table->model();
  QByteArray  bytes;
  for (int i = 0; i < model->rowCount(); i++)
  {
    for (int j = 0; j < model->columnCount(); j++)
    {
      if (j)
        bytes += ",";
      bytes += "\"" +
              model->data(model->index(i, j)).toString().replace("\"", "\"\"") +
              "\"";
    }
    bytes += "\n";
  }
  clipboard->setText(bytes);

  if (DEBUG)
    qDebug("ResultsOutput::copy() returning with bytes %s", bytes.data());
}

void ResultsOutput::createContextMenu(const QPoint & p)
{
  if (DEBUG)
    qDebug("ResultsOutput::createContextMenu(%d, %d)", p.x(), p.y());
  _copyAction->setEnabled(! _table->selectedItems().isEmpty());
  if (DEBUG)
    qDebug("_menu = %p\t_copyAction->enabled == %d",
           _menu, _copyAction->isEnabled());

  _menu->popup(mapToGlobal(p));
}
