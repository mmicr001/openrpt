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

#include "labeleditor.h"
#include "../../MetaSQL/metasql.h"

#include <QVariant>
#include <QFontDialog>
#include <QValidator>

LabelEditor::LabelEditor(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);


    // signals and slots connections
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnFont, SIGNAL(clicked()), this, SLOT(btnFont_clicked()));
    connect(rbVAlignBottom, SIGNAL(clicked()), this, SLOT(rbAlign_changed()));
    connect(tbText, SIGNAL(textChanged(const QString&)), this, SLOT(tbText_textChanged(const QString&)));
	connect(cbBuddy, SIGNAL(currentTextChanged(const QString&)), this, SLOT(buddy_textChanged(const QString&)));
    connect(rbHAlignNone, SIGNAL(clicked()), this, SLOT(rbAlign_changed()));
    connect(rbHAlignLeft, SIGNAL(clicked()), this, SLOT(rbAlign_changed()));
    connect(rbHAlignCenter, SIGNAL(clicked()), this, SLOT(rbAlign_changed()));
    connect(rbHAlignRight, SIGNAL(clicked()), this, SLOT(rbAlign_changed()));
    connect(rbVAlignNone, SIGNAL(clicked()), this, SLOT(rbAlign_changed()));
    connect(rbVAlignTop, SIGNAL(clicked()), this, SLOT(rbAlign_changed()));
    connect(rbVAlignMiddle, SIGNAL(clicked()), this, SLOT(rbAlign_changed()));

    leXPos->setValidator(new QDoubleValidator(0.0,100.0,3,leXPos));
    leYPos->setValidator(new QDoubleValidator(0.0,100.0,3,leYPos));
    
    leWidth->setValidator(new QDoubleValidator(0.01,100.0,3,leWidth));
    leHeight->setValidator(new QDoubleValidator(0.01,100.0,3,leHeight));
}

LabelEditor::~LabelEditor()
{
    // no need to delete child widgets, Qt does it all for us
}

void LabelEditor::setDocScene(DocumentScene * scene)
{
  ds = scene;
}

void LabelEditor::languageChange()
{
    retranslateUi(this);
}

void LabelEditor::rbAlign_changed()
{
    // ok one of the radio buttons was click.    
    // there are 8 radio buttons to check.
    // 4 in 2 groups: vertical and horizonatal group
    Qt::Alignment f = 0;
    if(rbHAlignLeft->isChecked()) f |= Qt::AlignLeft;
    if(rbHAlignCenter->isChecked()) f |= Qt::AlignHCenter;
    if(rbHAlignRight->isChecked()) f |= Qt::AlignRight;
    if(rbVAlignTop->isChecked()) f |= Qt::AlignTop;
    if(rbVAlignMiddle->isChecked()) f |= Qt::AlignVCenter;
    if(rbVAlignBottom->isChecked()) f |= Qt::AlignBottom;
    _alignment = f;
    labelPreview->setAlignment(_alignment);
}

void LabelEditor::btnFont_clicked()
{
    // pop up a font dialog
    bool ok;
    QFont font = QFontDialog::getFont(&ok, _font, this);
    if(ok) {
        _font = font;
        labelPreview->setFont(_font);
    }
}

void LabelEditor::tbText_textChanged( const QString & Str )
{
    _text = Str;
    // ok update the preview
    labelPreview->setText(_text);
}

void LabelEditor::buddy_textChanged( const QString & Str )
{
    // ok update the preview
    queryPreview->setText(getQueryResult(Str));
}

QString LabelEditor::getQueryResult(QString str)
{
  QDomNodeList sectionElem;
  QDomNode n;
  QDomElement sec;
  ParameterList plist;
  QString qry, col, result;
  XSqlQuery xqry; 
  
  // get parameter list
  sectionElem = ds->document().elementsByTagName("parameter");
  for (int i=0; i<sectionElem.size(); i++ )
  {
	sec = sectionElem.at(i).toElement();
	plist.append(sec.attribute("name"),sec.attribute("default"));
  }
  
  // find query of selected column and execute 
  sectionElem = ds->document().elementsByTagName("column");
  
  for(int i=0; i<sectionElem.size(); i++)
  {  
	if  (sectionElem.at(i).firstChild().nodeValue() == str)
	{
	  col = sectionElem.at(i).firstChild().nodeValue();
	  qry = sectionElem.at(i).previousSibling().firstChild().nodeValue();
	  break;
	}
  }
  
  if(qry=="Context Query")
	return QString();
   
  QSqlDatabase db = QSqlDatabase::database();
  if (!qry.isEmpty() && db.isOpen())
  {
    if(ds->qsList->get(qry)) //check if querysource name is valid
    {
      MetaSQLQuery mql = MetaSQLQuery(ds->qsList->get(qry)->query());
      xqry = mql.toQuery(plist,QSqlDatabase::database(),true);
      xqry.first();
      result = xqry.value(col).toString();
    }
    else 
      return QString();
  }
  
  return result;
}

void LabelEditor::setLabelFlags( int f )
{
    // set the label flags
    //qDebug("LabelEditor::setLabelFlags( 0x%X )",f);
    _alignment = (Qt::Alignment)f;
    labelPreview->setAlignment(_alignment);
    if((f & Qt::AlignLeft) == Qt::AlignLeft) {
        //qDebug("HAlignLeft 0x%X", AlignLeft);
        rbHAlignLeft->setChecked(true);
    } else if((f & Qt::AlignHCenter) == Qt::AlignHCenter) {
        //qDebug("HAlignCenter 0x%X", AlignHCenter);
        rbHAlignCenter->setChecked(true);
    } else if((f & Qt::AlignRight) == Qt::AlignRight) {
        //qDebug("HAlignRight 0x%X", AlignRight);
        rbHAlignRight->setChecked(true);
    } else {
        //qDebug("HAlignNone");
        rbHAlignNone->setChecked(true);
    }
    if((f & Qt::AlignTop) == Qt::AlignTop) {
        //qDebug("VAlignTop 0x%X", AlignTop);
        rbVAlignTop->setChecked(true);
    } else if((f & Qt::AlignVCenter) == Qt::AlignVCenter) {
        //qDebug("VAlignCenter 0x%X", AlignVCenter);
        rbVAlignMiddle->setChecked(true);
    } else if((f & Qt::AlignBottom) == Qt::AlignBottom) {
        //qDebug("VAlignBottom 0x%X", AlignBottom);
        rbVAlignBottom->setChecked(true);
    } else {
        //qDebug("VAlignNone");
        rbVAlignNone->setChecked(true);
    }
}

void LabelEditor::rbHAlignNone_clicked()
{

}

void LabelEditor::updatePreview()
{
    labelPreview->setAlignment(_alignment);
    labelPreview->setText(_text);
    labelPreview->setFont(_font);
}

void LabelEditor::showEvent(QShowEvent * e)
{
    QDialog::showEvent(e);
    updatePreview();
}
