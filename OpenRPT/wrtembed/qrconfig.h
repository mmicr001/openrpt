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

#ifndef QRCONFIG_H
#define QRCONFIG_H

#include <QWidget>
#include <QComboBox>
#include <QString>

namespace Ui {
    class QRConfig;
}

class QRConfig : public QWidget
{
    Q_OBJECT

public:
    explicit QRConfig(QWidget *parent = 0);
    ~QRConfig();
    QString format(const QString &align);

public slots:
    void setAutoSize(const bool &p);
    void setQRSize(const int &p);
    void setErrorCorrection(const int &p);

private slots:

signals:

private:
    Ui::QRConfig *ui;

};

#endif // QRCONFIG_H
