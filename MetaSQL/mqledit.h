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

#ifndef MQLEDIT_H
#define MQLEDIT_H

class LogOutput;
class ParameterEdit;
class ResultsOutput;
class QTextDocument;

#include <QWidget>
#include <QTimer>

#include "ui_mqledit.h"

#include "metasqlhighlighter.h"
#include "selectmql.h"
#include "finddialog.h"

class MQLEdit : public QWidget, public Ui::MQLEdit
{
    Q_OBJECT

  public:
    MQLEdit(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~MQLEdit();

                static QString       name();
    Q_INVOKABLE        QString       getMetaSQLText();
    Q_INVOKABLE        ParameterEdit*getParameterEdit();
    Q_INVOKABLE        QStringList   getParamsFromMetaSQLText();

  public slots:
    virtual void clear();
    virtual void editFind();
    virtual void execQuery();
    virtual void fileDatabaseConnect();
    virtual void fileDatabaseDisconnect();
    virtual void fileDatabaseOpen();
    virtual void fileDatabaseOpen(const int id);
    virtual bool fileDatabaseSaveAs();
    virtual void fileExit();
    virtual void fileNew();
    virtual void fileOpen();
    virtual void filePrint();
    virtual bool fileSave();
    virtual void fileSaveAs();
    virtual void forceTestMode(bool p);
    virtual void helpAbout();
    virtual void helpMqlSyntax();
    virtual void helpMqlEditor();
    virtual bool isReadOnly();
    virtual void parseQuery();
    virtual void populateParameterEdit();
    virtual void sMQLSelected(int id);
    virtual void setReadOnly(bool ro);
    virtual void showExecutedSQL();
    virtual void showLog();
    virtual void showResults();

  protected:
    enum DestType { MQLUnknown, MQLFile, MQLDatabase }; // Report, Widget, ???

    ResultsOutput *_results;
    QString        _fileName;
    int            _mqlGrade;
    QString        _mqlGroup;
    QString        _mqlName;
    QString        _mqlNotes;
    QString        _mqlSchema;
    SelectMQL     *_mqlSelector;
    ParameterEdit *_pEdit;
    LogOutput     *_log;
    LogOutput     *_sql;
    QTimer         _tick;

    virtual bool askSaveIfModified();
    virtual bool databaseSave();
    virtual QString getTitleString(DestType type);
    virtual bool save();
    virtual bool saveAs();
    virtual void sTick();
    virtual void setDestType(DestType type);

  protected slots:
    virtual void languageChange();

    virtual void showParamList();

  private:
    QTextDocument      *_document;
    MetaSQLHighlighter *_highlighter;
    DestType            _dest;
    FindDialog         *_find;
};

#endif // MQLEDIT_H
