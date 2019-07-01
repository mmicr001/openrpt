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

/*
 *     This file contains the class definitions used for rendering reports
 * and is based largely on top of the openReports.h file done by Jeffrey Lyon.
 */

#ifndef __ORRENDERER_H__
#define __ORRENDERER_H__

class orReportPrivate;
class QWidget;
class ParameterList;

#include <QDomDocument>
#include <QFont>
#include <QImage>
#include <QPainter>
#include <QPrinter>
#include <QSqlDatabase>
#include <QStringList>

class orReport {
  private:
    void constructor(const QString &);

    orReportPrivate *_internal;
    static QPrinter* multiPrinter;
    static QPainter* multiPainter;

  public:
    orReport(QSqlDatabase = QSqlDatabase());
    orReport(const QString &, QSqlDatabase = QSqlDatabase());
    orReport(const QString &, const QStringList &, QSqlDatabase = QSqlDatabase());
    orReport(const char *, const ParameterList &, QSqlDatabase = QSqlDatabase());
    orReport(const QString &, const ParameterList &, QSqlDatabase = QSqlDatabase());
    ~orReport();

    bool    render(QPainter *, QPrinter * = 0);
    bool    print(QPrinter *prtThis = 0, bool boolSetupPrinter = true, bool showPreview = false, QWidget *parent = 0);
    bool    exportToPDF( const QString& fileName );

    static bool    beginMultiPrint(QPrinter *);
    static bool    beginMultiPrint(QPrinter *, bool & userCanceled);
    static bool    endMultiPrint(QPrinter *);

    void    setWatermarkText(const QString &);
    void    setWatermarkFont(const QFont &);
    void    setWatermarkOpacity(unsigned char);      // 0..255 : default 25

    QString watermarkText();
    QFont   watermarkFont();
    unsigned char watermarkOpacity();

    void    setBackgroundImage(const QImage &);
    void    setBackgroundRect(const QRect &);
    void    setBackgroundRect(int, int, int, int); 
    void    setBackgroundOpacity(unsigned char);     // 0..255 : default 25
    void    setBackgroundAlignment(int);             // Qt::AlignmentFlags
    void    setBackgroundScale(bool);
    void    setBackgroundScaleMode(Qt::AspectRatioMode);

    QImage  backgroundImage();
    QRect   backgroundRect();
    unsigned char backgroundOpacity();
    int     backgroundAlignment();
    bool    backgroundScale();
    Qt::AspectRatioMode backgroundScaleMode();
    
    void    setDatabase(QSqlDatabase);

    bool    setDom(const QDomDocument &docPReport);
    void    setParamList(const QStringList &);
    void    setParamList(const ParameterList &);
    ParameterList getParamList();
    bool    isValid();
    bool    doesReportExist();
    bool    doParamsSatisfy();
    bool    satisfyParams(QWidget *);
    int     reportError(QWidget *);
};

#endif

