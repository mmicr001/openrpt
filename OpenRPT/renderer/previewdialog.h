///////////////////////////////////////////////////////////////////////////////
// previewdialog.h
// -------------------
// This file is part of the OpenRPT report writer and rendering engine,
// and is Copyright (c) 2001-2019 by OpenMFG LLC, d/b/a xTuple,
// portions are Copyright (C) 2007 by David Johnson.  It
// is licensed to you under the xTuple End-User License Agreement ("the
// EULA"), the full text of which is available at www.xtuple.com/EULA.
// While the EULA gives you access to source code and encourages your
// involvement in the development process, this Package is not free
// software.  By using this software, you agree to be bound by the
// terms of the EULA.
///////////////////////////////////////////////////////////////////////////////

#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QAbstractScrollArea>
#include <QDialog>

class PreviewWidget;
class QAbstractScrollArea;
class ORODocument;
class QPrinter;

///////////////////////////////////////////////////////////////////////////////
/// \class PreviewDialog
/// PreviewDialog is a print preview dialog for use with the TextPrinter class.
/// It is typically created with the TextPrinter::preview() method.
///////////////////////////////////////////////////////////////////////////////

class PreviewDialog : public QDialog
{
    Q_OBJECT
public:
    /// Construct a PreviewDialog dialog
    PreviewDialog(ORODocument *document,
                  QPrinter *pPrinter,
                  QWidget *parent=0);
    /// Destructor
    virtual ~PreviewDialog();

private:
    PreviewWidget *_view;
};

// Text preview widget
class PreviewWidget : public QAbstractScrollArea
{
    Q_OBJECT
public:
    PreviewWidget(ORODocument *document,
                  QPrinter *pPrinter,
                  QWidget *parent=0);
    virtual ~PreviewWidget();
    void updateView();

private slots:
    // zoom preview
    void zoomIn();
    void zoomOut();

private:
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    QRectF paperRect(QPaintDevice *device);
    int columnWidth();
    int nbColumns();


private:
    ORODocument * _doc;
    QPrinter *	_pPrinter;
    double _zoom;
    QPoint mousepos;
    QPoint scrollpos;
};

#endif // PREVIEWDIALOG_H
