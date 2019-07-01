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

#ifndef LABELEDITOR_H
#define LABELEDITOR_H

#include <QDialog>
#include "documentscene.h"
#include "ui_labeleditor.h"

class LabelEditor : public QDialog, public Ui::LabelEditor
{
    Q_OBJECT

public:
    LabelEditor(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~LabelEditor();
    inline virtual Qt::Alignment alignment()  { return _alignment; };
    inline virtual QString text()  { return _text; };
    inline virtual QFont font() { return _font; };
	void setDocScene(DocumentScene * scene);
	QString getQueryResult(QString str);

public slots:
    virtual void rbAlign_changed();
    virtual void btnFont_clicked();
    virtual void tbText_textChanged(const QString & Str);
	virtual void buddy_textChanged( const QString & Str );
    virtual void setLabelFlags(int f);
    virtual void rbHAlignNone_clicked();
    inline virtual void setAlignment(const Qt::Alignment& p)  { _alignment = p; };
    inline virtual void setText(const QString& p)  { _text = p; };
    inline virtual void setFont(const QFont& p)  { _font = p; };
    virtual void updatePreview();

protected:
    virtual void showEvent(QShowEvent*);

protected slots:
    virtual void languageChange();

private:
	DocumentScene * ds;
    Qt::Alignment _alignment;
    QString _text;
    QFont _font;

};

#endif // LABELEDITOR_H
