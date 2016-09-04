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
