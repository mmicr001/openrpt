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

void renderPDF417(QPainter *painter, int /*dpi*/, const QRectF &r, const QString &_str, OROBarcode *bc)
{
  QByteArray ba = QByteArray(bc->format().toStdString().c_str(), bc->format().toStdString().length());
  QJsonDocument doc = QJsonDocument::fromJson(ba);
  QJsonObject obj = doc.object();
  QJsonValue codewords = obj.value("codewords");
  QJsonValue columns = obj.value("columns");
  QJsonValue errorCorrection = obj.value("errorCorrection");
  QJsonValue type = obj.value("type");

  QPen pen(Qt::NoPen);
  QBrush brush(QColor("black"));
  painter->save();
  painter->setPen(pen);
  painter->setBrush(brush);

  QString str = _str;
  BarcodeItem bci;
  bci.ar=(Zint::QZint::AspectRatioMode)0;
  bci.bc.setText(str);
  bci.bc.setSecurityLevel(errorCorrection.toInt());
  bci.bc.setWidth(columns.toInt());
  bci.bc.setInputMode(UNICODE_MODE);
  if (type.toString() == "truncated")
      bci.bc.setSymbol(BARCODE_PDF417TRUNC);
  else
      bci.bc.setSymbol(BARCODE_PDF417);
  bci.bc.setPdf417CodeWords(codewords.toInt());
  //bci.bc.setBorderType((Zint::QZint::BorderType)(0));
  //bci.bc.setBorderWidth(0);
  //bci.bc.setHeight(50); //0-300
  bci.bc.setWhitespace(0);
  bci.bc.setFgColor(QColor("black"));
  bci.bc.setBgColor(QColor("white"));
  bci.update();

  bci.paint(painter, r);
  bci.update();

  painter->restore();
  return;
}
