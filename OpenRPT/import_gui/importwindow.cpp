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

#include "importwindow.h"
#include <QInputDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QTimerEvent>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <QStringList>
#include <QDomNode>
#include <QDesktopServices>

#include "xsqlquery.h"
#include "data.h"

#include "builtinSqlFunctions.h"

ImportWindow::ImportWindow(QWidget* parent, Qt::WindowFlags fl)
    : QMainWindow(parent, fl)
{
  setupUi(this);

  (void)statusBar();

  // signals and slots connections
  connect(helpRefGuideAction, SIGNAL(triggered()), this, SLOT(helpRefGuide()));
  connect(helpAboutAction, SIGNAL(triggered()), this, SLOT(helpAbout()));
  connect(fileExitAction, SIGNAL(triggered()), this, SLOT(fileExit()));
  connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(sAdd()));
  connect(_add, SIGNAL(clicked()), this, SLOT(sAdd()));
  connect(_import, SIGNAL(clicked()), this, SLOT(sImport()));
  connect(_remove, SIGNAL(clicked()), this, SLOT(sRemove()));
  connect(_reports, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(reportsDoubleClicked(QListWidgetItem*)));

  _reports->clear();
  _dbTimerId = startTimer(60000);

  _package->addItem("");

  XSqlQuery qry;
  qry.exec(getSqlFromTag("fmt21", QSqlDatabase::database().driverName()));
  while(qry.next())
  {
    _package->addItem(qry.value("package").toString());
  }
}

ImportWindow::~ImportWindow()
{
    // no need to delete child widgets, Qt does it all for us
}

void ImportWindow::languageChange()
{
    retranslateUi(this);
}

void ImportWindow::helpRefGuide()
{
  QDesktopServices::openUrl(QUrl("https://xtupleuniversity.xtuple.com/sites/default/files/prodguide/openrpt/ch05s02s01.html"));
}


void ImportWindow::helpAbout()
{
  QMessageBox::about(this, tr("Report Import Tool"),
                     tr("%1 version %2\n%3, All Rights Reserved\nBuild: %4\n"
                        "\n%5 is a tool for importing report definition files "
                        "into a database.")
                     .arg(OpenRPT::name, OpenRPT::version, OpenRPT::copyright,
                          OpenRPT::build, OpenRPT::name));
}


void ImportWindow::fileExit()
{
  qApp->closeAllWindows();
}


void ImportWindow::sAdd()
{
  QStringList files = QFileDialog::getOpenFileNames(this, tr("Select one or more reports to open"), QString::null,
                                                    tr("Report Definitions (*.xml)"));
  if(!files.isEmpty())
    for(QStringList::Iterator it = files.begin(); it != files.end(); ++it)
      _reports->addItem(*it);
}


void ImportWindow::sRemove()
{
  QList<QListWidgetItem *> list = _reports->selectedItems();
  for(int i = 0; i < list.count(); i++)
  {
    _reports->removeItemWidget(list.at(i));
    delete list.at(i);
  }
}


void ImportWindow::sImport()
{
  _log->append(tr("Import Started..."));
  QListWidgetItem * item = 0;
  QList<QListWidgetItem *> list = _reports->selectedItems();
  for(int i = 0; i < list.count(); i++)
  {
    item = list.at(i);
    QString xml_file = item->text();

    QString report_name  = QString::null;
    QString report_desc  = QString::null;
    QString report_src   = QString::null;
    int     report_grade = item->data(Qt::UserRole).toInt();

    if(!xml_file.isEmpty())
    {
      QFile file(xml_file);
      if(file.open(QIODevice::ReadOnly))
      {
        QDomDocument doc;
        QString errMsg;
        int errLine, errCol;
        if(doc.setContent(&file, &errMsg, &errLine, &errCol))
        {
          QDomElement root = doc.documentElement();
          if(root.tagName() == "report")
          {
            for(QDomNode n = root.firstChild();
                  !n.isNull(); n = n.nextSibling())
            {
              if(n.nodeName() == "name")
                report_name = n.firstChild().nodeValue();
              else if(n.nodeName() == "description")
                report_desc = n.firstChild().nodeValue();
            }
            report_src = doc.toString();

            if(!report_name.isEmpty())
            {
              XSqlQuery qry;
              XSqlQuery qry2;
              XSqlQuery query;

              qry.prepare(getSqlFromTag("fmt09", QSqlDatabase::database().driverName()));	// MANU
              qry.bindValue(":report_name",  report_name);	// MANU
              qry.bindValue(":report_grade", report_grade);	// MANU
              qry.exec();
              if(qry.first())
              {
                QString oldPackage;
                qry2.prepare(getSqlFromTag("fmt20", QSqlDatabase::database().driverName()));
                qry2.bindValue(":report_id", qry.value(0));
                qry2.exec();
                if(qry2.first())
                  oldPackage = qry2.value("package").toString();

                if(_package->currentText()==oldPackage)
                {
                  // update
                  query.prepare(getSqlFromTag("fmt10", QSqlDatabase::database().driverName()));   // MANU
                  query.bindValue(":report_desc", report_desc);           // MANU
                  query.bindValue(":report_src",   report_src);           // MANU
                  query.bindValue(":report_id", qry.value(0));            // MANU
                  query.bindValue(":report_name",  report_name);  // MANU
                }
                else
                {
                  //move record
                  QString tablename;
                  qry2.prepare(getSqlFromTag("fmt22", QSqlDatabase::database().driverName()));
                  if (!_package->currentText().isEmpty())
                    qry2.bindValue(":package", _package->currentText());
                  qry2.exec();
                  if(qry2.first())
                    tablename = qry2.value("tablename").toString();

                  query.prepare(getSqlFromTag("fmt23", QSqlDatabase::database().driverName()).arg(tablename));
                  query.bindValue(":report_id", qry.value(0));
                  query.bindValue(":report_name", report_name);
                  query.bindValue(":report_desc",report_desc);
                  query.bindValue(":report_src", report_src);
                  query.bindValue(":report_grade", report_grade);
                }
              }
              else
              {
                // insert
                QString tablename;
                qry2.prepare(getSqlFromTag("fmt22", QSqlDatabase::database().driverName()));
                if (!_package->currentText().isEmpty())
                  qry2.bindValue(":package", _package->currentText());
                qry2.exec();
                if(qry2.first())
                  tablename = qry2.value("tablename").toString();

                query.prepare(getSqlFromTag("fmt24", QSqlDatabase::database().driverName()).arg(tablename));
                query.bindValue(":report_name",  report_name);	// MANU
                query.bindValue(":report_desc", report_desc);		// MANU
                query.bindValue(":report_src",   report_src);		// MANU
                query.bindValue(":report_grade", report_grade);	// MANU
              }
              
              if(!query.exec())
              {
                QSqlError err = query.lastError();
                _log->append(tr("<font color=red>The following error was encountered while trying to import %1 into the database:\n"
                                "\t%2\n\t%3\n</font>")
                              .arg(xml_file)
                              .arg(err.driverText())
                              .arg(err.databaseText()));
              }
              else
                _log->append(tr("Import successful of %1").arg(xml_file));
            }
            else
              _log->append(tr("<font color=orange>The document %1 does not have a report name defined\n</font>")
                            .arg(xml_file));
          }
          else
            _log->append(tr("<font color=red>XML Document %1 does not have root node of report\n</font>")
                          .arg(xml_file));
        }
        else
          _log->append(tr("<font color=red>Error parsing file %1: %2 on line %3 column %4\n</font>")
                        .arg(xml_file).arg(errMsg).arg(errLine).arg(errCol));
      }
      else
        _log->append(tr("<font color=red>Could not open the specified file: %1\n</font>")
                      .arg(xml_file));
    }
    else
      _log->append("<font color=red>Encountered and empty entry: No file name was given.\n</font>");
  }
  _log->append(tr("Import complete!\n\n\n"));
}


void ImportWindow::timerEvent( QTimerEvent * e )
{
  if(e->timerId() == _dbTimerId)
  {
    QSqlDatabase db = QSqlDatabase::database(QSqlDatabase::defaultConnection,false);
    if(db.isValid())
    {
      QSqlQuery qry(getSqlFromTag("fmt07", db.driverName()));		// MANU
    }
    // if we are not connected then we have some problems!
  }
}


void ImportWindow::reportsDoubleClicked( QListWidgetItem * item )
{
  if(!item)
    return;

  bool ok = false;
  int grade = QInputDialog::getInteger(this, tr("Edit Grade"), tr("Grade: "), item->data(Qt::UserRole).toInt(), 0, 99, 1, &ok);
  if(ok)
    item->setData(Qt::UserRole, grade);
}

