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

#ifndef __RENDERER_CROSSTAB_H__
#define __RENDERER_CROSSTAB_H__

// Storage structure
typedef QPair <QString, QString> CrossTabStorageKey;
typedef QMap  <CrossTabStorageKey, QString> CrossTabStorage;

//////////////////////////////////////////////////////////////////////////////
// Helper class for row properties
//////////////////////////////////////////////////////////////////////////////
class CrossTabRow
{
public:
  CrossTabRow (): m_rowMaxHeight(0), m_rowVAlign(Qt::AlignVCenter) {};
  ~CrossTabRow (){};

  int m_rowMaxHeight;
  Qt::AlignmentFlag m_rowVAlign;
};

typedef QString CrossTabRowIndexKey;
typedef QMap <CrossTabRowIndexKey, CrossTabRow> CrossTabRowIndex;

//////////////////////////////////////////////////////////////////////////////
// Helper class for column properties
//////////////////////////////////////////////////////////////////////////////
class CrossTabColumn
{
public:
  CrossTabColumn (): m_columnMaxWidth(0), m_columnHAlign(Qt::AlignHCenter) {};
  ~CrossTabColumn (){};

  int m_columnMaxWidth;
  Qt::AlignmentFlag m_columnHAlign;
};

typedef QString CrossTabColumnIndexKey;
typedef QMap <CrossTabColumnIndexKey, CrossTabColumn> CrossTabColumnIndex;

//////////////////////////////////////////////////////////////////////////////
// Helper class for table properties
//////////////////////////////////////////////////////////////////////////////
class CrossTabTable
{
public:
  CrossTabTable (): m_tableMaxHeight(0), m_tableMaxWidth(0), m_tableVAlign(Qt::AlignLeft) {};
  ~CrossTabTable (){};

  int m_tableMaxHeight;
  int m_tableMaxWidth;
  Qt::AlignmentFlag m_tableVAlign;
};


//////////////////////////////////////////////////////////////////////////////
// Wrap policy:
// First all columns than all rows. Left to right, top to bottom.
//////////////////////////////////////////////////////////////////////////////
class CrossTab
{

public:
  CrossTab(const QFont&);
  virtual ~CrossTab();

  void Initialize(ORCrossTabData&, const QMap<QString,QColor>&);

  void Iterate();

  void SetTableWrappingPolicy(const bool& displayAllColumnsFirst);
  bool GetTableWrappingPolicy();

  void SetAutoRepaint(bool &);
  bool AutoRepaint();

  void    SetValue(const QString&, const QString&, const QString&);
  QString GetValue(const QString&, const QString&);

  void  SetFont(const QFont&);
  QFont GetFont() const;

  void PopulateFromQuery(XSqlQuery*);

  void CalculateCrossTabMeasurements(void);
  
  void CalculateDisplayedRowsAndColumns(int& lastColumn, int& lastRow, QRect& rect);

  void CalculateSize(QRect& rect);

  void CalculateTableSize(QRect& rect);

  void CalculateNextRowSize(int& height);

  void clear();

  bool AllDataRendered();

  void SetRect(const QRect& boundedRectangle);
  QRect rect();
  void SetWidth(const int& width);
  int width();
  void SetHeight(const int& height);
  int height();

  void repaint(void);

  virtual void Draw(QPainter &); 

protected:
  QRect                m_boundedRectangle;
  ORCrossTabData       m_crossTabData;
  QMap<QString,QColor> m_colorMap;
  QMap<QString,Qt::Alignment> m_hAlignMap;
  QMap<QString,Qt::Alignment> m_vAlignMap;

  QFont               m_commonFont;
  CrossTabStorage     m_data;
  CrossTabRowIndex    m_rowIndex;
  CrossTabColumnIndex m_columnIndex;
  CrossTabTable       m_tableProperties;

  int                 m_cellLeftMargin;
  int                 m_cellRightMargin;
  int                 m_cellTopMargin;
  int                 m_cellBottomMargin;
  bool                m_autoRepaint;

  int                 m_rowIndexStored;             // See CrossTab::Iterate
  int                 m_columnIndexStored;          // See CrossTab::Iterate
  int                 m_columnIndexStoredIteration; // See CrossTab::Iterate
  int                 m_rowIndexStoredIteration;    // See CrossTab::Iterate
  int                 m_columnIndexStoredLast;      // See CrossTab::Iterate
  int                 m_rowIndexStoredLast;         // See CrossTab::Iterate

  bool                m_columnHeaderEachPage;
  bool                m_rowHeaderEachPage;

  bool                m_tableWrapDisplayAllColumnsFirst;

  bool                m_populated;

  int                 m_dpiX;
  int                 m_dpiY;

  QRect               m_rect;
};

#endif //__RENDERER_CROSSTAB_H__

