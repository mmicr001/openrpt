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

#include "quuencode.h"

#include <QString>
#include <QIODevice>
#include <QTextStream>
#include <QBuffer>
#include <QChar>

#define ENC(c) ((c) ? ((c) & 077) + ' ': '`')
#define DEC(c) (((c) - ' ') & 077)

QString QUUEncode(QIODevice & iod, const QString & _remote, int mode) {
    QString value;
    QString remote = _remote;
    if(!iod.isOpen()) {
        if(!iod.open(QIODevice::ReadOnly)) {
            qDebug("Could not open the QIODevice for reading.");
            return QString::null;
        }
    }

    if(remote == QString::null) remote = "internal";
    if(mode == 0) mode = 0644;

    value = QString().sprintf("begin %o %s\n", mode, remote.toLatin1().data());

    qint64 nr = 0;
    char data[45];
    char c;
    char * b;
    while( (nr = iod.read(&data[0], 45)) > 0 ) {
        c = ENC(nr);
        value += c;
        for(b = data; nr > 0; nr -= 3, b += 3) {
            c = b[0] >> 2;
            c = ENC(c);
            value += c;
            c = ((b[0] << 4) & 060) | ((b[1] >> 4) & 017);
            c = ENC(c);
            value += c;
            c = ((b[1] << 2) & 074) | ((b[2] >> 6) & 03);
            c = ENC(c);
            value += c;
            c = b[2] & 077;
            c = ENC(c);
            value += c;
        }
        value += '\n';
    }
    c = ENC('\0');
    value += c;
    value += "\nend\n";

    return value;
}

QByteArray QUUDecode(const QString & _source, QString * name, int * mode) {
    QString source = _source;
    QByteArray b;
    if(source.isEmpty()) return b;

    QTextStream in(&source, QIODevice::ReadOnly);

    QString l;
    // find the start of the UUEncoded data
    while( ((l = in.readLine()) != QString::null) && (!l.startsWith("begin ")) );
    if(!l.startsWith("begin ")) {
        return b; // not UUEncoded data, returns empty array    
    }

    QTextStream tin(&l, QIODevice::ReadOnly);
    QString _begin, _name, _mode;
    tin >> _begin;
    tin >> _mode;
    tin >> _name;

    if(_begin != "begin") {
        qDebug("We may have a problem. Header not parsed correctly.");
    }

    if(name != 0) {
        *name = _name;
    }
    QChar qc;
    char c;
    if(mode != 0) {
        *mode = 0;
        for(int i = 0; i < _mode.length(); i++) {
            qc = _mode.at(i);
            c = qc.toLatin1();
            c -= '0'; // convert the ascii value to the decimal value
            *mode = (*mode << 3) | (c & 07);
        }
    }

    QBuffer buf(&b);
    buf.open(QIODevice::WriteOnly);

    int num = 0;
    char c0, c1, c2, c3;
    while( ((l = in.readLine()) != QString::null) && (!l.startsWith("end")) ) {
        qc = l[0];
        c = qc.toLatin1();
        num = DEC(c);
        for(int p = 1; num > 0; p += 4, num -= 3) {
            if(num >= 3) {
                qc = l[p + 0];
                c0 = qc.toLatin1();
                qc = l[p + 1];
                c1 = qc.toLatin1();
                qc = l[p + 2];
                c2 = qc.toLatin1();
                qc = l[p + 3];
                c3 = qc.toLatin1();

                c = DEC(c0) << 2 | DEC(c1) >> 4;
                buf.putChar(c);
                c = DEC(c1) << 4 | DEC(c2) >> 2;
                buf.putChar(c);
                c = DEC(c2) << 6 | DEC(c3);
                buf.putChar(c);
            } else {
                if(num >= 1) {
                    qc = l[p + 0];
                    c0 = qc.toLatin1();
                    qc = l[p + 1];
                    c1 = qc.toLatin1();

                    c = DEC(c0) << 2 | DEC(c1) >> 4;
                    buf.putChar(c);
                }
                if(num >= 2) {
                    qc = l[p + 1];
                    c1 = qc.toLatin1();
                    qc = l[p + 2];
                    c2 = qc.toLatin1();

                    c = DEC(c1) << 4 | DEC(c2) >> 2;
                    buf.putChar(c);
                }
            }
        }
    }

    if(!l.startsWith("end")) {
        qDebug("We seem to have run out of file before we were finished.");
    }

    return b;
}
