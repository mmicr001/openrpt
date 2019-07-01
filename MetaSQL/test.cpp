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

#include <qstring.h>
#include <qstringlist.h>

#include <qfile.h>
#include <qtextstream.h>

#include "metasql.h"

int main(int /*argc*/, const char * /*argv*/[]) {
    QTextOStream qout(stdout);

    QFile file("test.mql");
    if(file.open(IO_ReadOnly)) {
        QTextStream stream(&file);
        QString query = stream.read();
        file.close();

        MetaSQLQuery mql(query);

        if(mql.isValid()) {
            ParameterList params;
            params.append("classcode_code", QVariant("^MA"));
            qout << "The parsed query generated a valid object." << endl;
            XSqlQuery qry = mql.toQuery(params);
            while(qry.next()) {
                qDebug("row");
            }
        } else {
            qout << "The parsed query did not generate a valid object." << endl;
        }
    } else {
        qout << "Unable to open '" << file.name() << "' for reading." << endl;
    }

    return 0;
}
