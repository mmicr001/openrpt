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
