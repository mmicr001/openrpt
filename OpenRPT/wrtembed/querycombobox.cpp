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

#include "querycombobox.h"

QueryComboBox::QueryComboBox(QWidget *parent)
  : QComboBox(parent)
{
}

QueryComboBox::~QueryComboBox()
{
}

void QueryComboBox::init (QuerySourceList * qsl, const QString &query, bool paramAndContextQueries)
{
  // populate the combo item and set it to an appropriate value
  clear();
  int selected_index = -1;
  if(paramAndContextQueries) {
    addItem(tr("Context Query"));
    if(query == "Context Query") selected_index = 0;
    addItem(tr("Parameter Query"));
    if(query == "Parameter Query") selected_index = 1;
  }
  if(qsl != NULL) {
    for(unsigned int i = 0; i < qsl->size(); i++) {
      addItem(qsl->get(i)->name());
      if(query == qsl->get(i)->name()) {
        selected_index = i + (paramAndContextQueries ? 2 : 0);
      }
    }
  } else {
    qDebug("QuerySourceList is null");
  }
  if(selected_index == -1) {
    addItem(QObject::tr("-- Select Query --"),0);
    selected_index = 0;
  }
  setCurrentIndex(selected_index);  
}

QString QueryComboBox::currentQuery ()
{
  QString qrystr = currentText();
  if(qrystr == tr("-- Select Query --")) qrystr = QString::null;
  if(qrystr == tr("Parameter Query")) qrystr = "Parameter Query";
  if(qrystr == tr("Context Query")) qrystr = "Context Query";

  return qrystr;
}

