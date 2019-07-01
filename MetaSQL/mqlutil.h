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

#ifndef __MQLUTIL_H__
#define __MQLUTIL_H__

#include <QString>

#include "metasql.h"

class MQLUtil {
  public:
    static bool extractMetadata(const QString &query, QString &group, QString &name, QString &notes);
    static bool rewriteMetadata(QString &query, const QString &group, const QString &name, const QString &notes);

    static QString mqlLoad(const QString &name, QString &errmsg, bool *valid);
    static QString mqlLoad(const QString &group, const QString &name, QString &errmsg, bool *valid);
    Q_INVOKABLE static QStringList getParamsFromText(const QString p);
};

// backwards compatibility functions for xtuple sources
QString mqlLastError();
void    mqlClearLastError();
MetaSQLQuery mqlLoad(const QString &name, bool *valid = 0);
MetaSQLQuery mqlLoad(const QString &group, const QString &name, bool *valid = 0);

#endif
