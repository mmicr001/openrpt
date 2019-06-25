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
#ifndef __ORPRERENDER_H__
#define __ORPRERENDER_H__

#include "parsexmlutils.h"
#include "orutils.h"

#include <QSqlDatabase>
#include <QDomDocument>
#include <QRectF>
#include <QString>
#include <QFont>

class ORPreRenderPrivate;
class ParameterList;
class ORODocument;

//
// ORPreRender
// This class takes a report definition and prerenders the result to
// an ORODocument that can be used to pass to any number of renderers.
//
class ORPreRender {
  public:

    ORPreRender(QSqlDatabase = QSqlDatabase());
    ORPreRender(const QDomDocument &, QSqlDatabase = QSqlDatabase());
    ORPreRender(const QDomDocument &, const ParameterList &, QSqlDatabase = QSqlDatabase());
    virtual ~ORPreRender();

    ORODocument * generate();

    void setDatabase(QSqlDatabase);
    QSqlDatabase database() const;

    bool setDom(const QDomDocument &);
    void setParamList(const ParameterList &);
    ParameterList paramList() const;

    bool isValid() const;
    bool doParamsSatisfy() const;

    void setWatermarkText(const QString &);
    void setWatermarkFont(const QFont &);
    void setWatermarkOpacity(unsigned char); // 0..255 : default 25

    QString watermarkText() const;
    QFont watermarkFont() const;
    unsigned char watermarkOpacity() const;

    void setBackgroundImage(const QImage &);
    void setBackgroundRect(const QRectF &);
    void setBackgroundRect(double, double, double, double);
    void setBackgroundOpacity(unsigned char);
    void setBackgroundAlignment(int);
    void setBackgroundScale(bool);
    void setBackgroundScaleMode(Qt::AspectRatioMode mode);

    QImage backgroundImage() const;
    QRectF backgroundRect() const;
    unsigned char backgroundOpacity() const;
    int backgroundAlignment() const;
    bool backgroundScale() const;
    Qt::AspectRatioMode backgroundScaleMode() const;
	
	bool populateData(const ORDataData& dataSource, orData &dataTarget);
	QString evalField(ORFieldData* f, QString* outColorStr=0);
  protected:

  private:
    ORPreRenderPrivate* _internal;
};


#endif // __ORPRERENDER_H__
