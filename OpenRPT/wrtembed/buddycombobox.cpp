/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2018 by OpenMFG, LLC
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
  if(findText(buddy)==-1)
	setCurrentIndex(0);
  else
	setCurrentIndex(findText(buddy));
}

QString BuddyComboBox::currentField ()
{
  return (currentIndex() > 0) ? currentText() : QString::null;
}

