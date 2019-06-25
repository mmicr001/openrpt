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

#ifndef METASQLSAVEPARAMETERS_H
#define METASQLSAVEPARAMETERS_H

#include <QDialog>
#include <QString>

#include "ui_metasqlsaveparameters.h"

class MetaSQLSaveParameters : public QDialog, public Ui::MetaSQLSaveParameters
{
  Q_OBJECT

  public:
    MetaSQLSaveParameters(QWidget *parent = 0, Qt::WindowFlags fl = 0);
    ~MetaSQLSaveParameters();

    int     grade()     const;
    QString group()     const;
    QString name()      const;
    QString notes()     const;
    QString schema()    const;

  public slots:
    void    setGrade(const  int     p);
    void    setGroup(const  QString p);
    void    setName(const   QString p);
    void    setNotes(const  QString p);
    void    setSchema(const QString p);

  protected slots:
    virtual void languageChange();
    virtual void sGetGroups();
};

#endif
