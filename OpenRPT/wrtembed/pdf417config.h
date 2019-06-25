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

#ifndef PDF417CONFIG_H
#define PDF417CONFIG_H

#include <QWidget>
#include <QComboBox>
#include <QString>

namespace Ui {
    class PDF417Config;
}

class PDF417Config : public QWidget
{
    Q_OBJECT

public:
    explicit PDF417Config(QWidget *parent = 0);
    ~PDF417Config();
    QString format(const QString &align);
    enum BCType { Standard, Truncated, HIBC };

public slots:
    void setCodewords(const int &p);
    void setColumns(const int &p);
    void setErrorCorrecton(const int &p);
    void setType(const BCType &type);

private slots:

signals:

private:
    Ui::PDF417Config *ui;

};

#endif // PDF417CONFIG_H
