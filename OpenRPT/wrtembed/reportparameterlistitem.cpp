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

#include "reportparameterlistitem.h"

#include <QVariant>

ReportParameterListItem::ReportParameterListItem(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);


    // signals and slots connections
    connect(_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(_accept, SIGNAL(clicked()), this, SLOT(accept()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
ReportParameterListItem::~ReportParameterListItem()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ReportParameterListItem::languageChange()
{
    retranslateUi(this);
}

