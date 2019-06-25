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

#include "buddycombobox.h"

BuddyComboBox::BuddyComboBox(QWidget *parent)
  : QComboBox(parent)
{
}

BuddyComboBox::~BuddyComboBox()
{
}

void BuddyComboBox::init(QStringList fields, QString buddy)
{
  // populate the combo item and set it to an appropriate value
  clear();
  
  fields.sort();
  if( !fields.isEmpty() ) 
	addItems(fields);
  else 
    qDebug("QuerySourceList is null");

  insertItem(0,"-- Select Field/Textarea --");
  setCurrentIndex(0);
  
  if(buddy.isEmpty())
	return;
  if(findText(buddy)!=-1)
	setCurrentIndex(findText(buddy));
}

QString BuddyComboBox::currentField ()
{
  return (currentIndex() > 0) ? currentText() : QString::null;
}

