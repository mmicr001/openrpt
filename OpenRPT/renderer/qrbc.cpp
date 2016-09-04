#include <QString>
#include <QRectF>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "parsexmlutils.h"
#include "renderobjects.h"
#include "barcodeitem.h"
#include "zint.h"

void renderQR(QPainter *painter, int /*dpi*/, const QRectF &r, const QString &_str, OROBarcode *bc)
{
  QByteArray ba = QByteArray(bc->format().toStdString().c_str(), bc->format().toStdString().length());
  QJsonDocument doc = QJsonDocument::fromJson(ba);
  QJsonObject obj = doc.object();
  QJsonValue size = obj.value("size");
  QJsonValue autosize = obj.value("autosize");
  QJsonValue errorCorrection = obj.value("errorCorrection");

  QPen pen(Qt::NoPen);
  QBrush brush(QColor("black"));
  painter->save();
  painter->setPen(pen);
  painter->setBrush(brush);

  QString str = _str;
  BarcodeItem bci;
  bci.ar=(Zint::QZint::AspectRatioMode)0;
  bci.bc.setText(str);
  if (errorCorrection.toInt() >= 0)
      bci.bc.setSecurityLevel(errorCorrection.toInt());
  if (!autosize.toBool())
      bci.bc.setWidth(size.toInt());

  bci.bc.setInputMode(UNICODE_MODE);
  bci.bc.setSymbol(BARCODE_QRCODE);
  bci.bc.setWhitespace(0);
  bci.bc.setFgColor(QColor("black"));
  bci.bc.setBgColor(QColor("white"));
  bci.update();

  bci.paint(painter, r);
  bci.update();

  painter->restore();
  return;
}
