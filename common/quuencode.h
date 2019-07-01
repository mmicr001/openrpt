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

#ifndef __QUUENCODE_H__
#define __QUUENCODE_H__

#include <QString>

class QIODevice;

QString    QUUEncode(QIODevice &, const QString & = QString::null, int mode = 0);
QByteArray QUUDecode(const QString &, QString * = 0, int * = 0);

#endif

