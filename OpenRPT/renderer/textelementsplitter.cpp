#include <QtGui>

#include "orprerender.h"
#include "renderobjects.h"
#include "orutils.h"
#include <xsqlquery.h>
#include <parsexmlutils.h>
#include "textelementsplitter.h"

#include <QPrinter>
#include <QFontMetrics>
#include <QPainter>

#define CLIPMARGIN 10

TextElementSplitter::TextElementSplitter(ORObject *textelem, QString text, qreal leftMargin, qreal yOffset, qreal pageBottom) :
  _text(text), _leftMargin(leftMargin), _yOffset(yOffset), _pageBottom(pageBottom), _lineCounter(0)
{   
  _element = textelem->toText();

  if (_text.isEmpty())
  {
    return;
  }

  QPointF pos = _element->rect.topLeft();
  QSizeF size(_element->rect.width(), _element->rect.height());
  pos /= 100.0;
  pos += QPointF(_leftMargin, 0);
  size /= 100.0;

  QImage prnt(1, 1, QImage::Format_RGB32);

  _baseElementRect = QRectF(pos, size);

#ifdef Q_WS_MAC // bug 13284, 15118
  if(_element->align & Qt::AlignRight)
    _baseElementRect.setLeft(_baseElementRect.left() - CLIPMARGIN / 100.0);
  else
    _baseElementRect.setRight(_baseElementRect.right() + CLIPMARGIN / 100.0);
#endif

  _lineClipWidth = (int)(_baseElementRect.width() * prnt.logicalDpiX()) - CLIPMARGIN;

  _fm = QSharedPointer<QFontMetrics>(new QFontMetrics(_element->font, &prnt));
}

void TextElementSplitter::nextLine()
{  
  _currentLine.clear();
  int currentPos = 0;
  bool textShouldWrap = false;

  if(_fm->boundingRect(_text).width() > _lineClipWidth)
    textShouldWrap = true;

  if(!textShouldWrap)
  {
    _currentLine = _text;
    
    //check for newline character
    QRegExp re("(\r\n|\n)");
    int newline = re.indexIn(_text);
    if (newline !=-1)
    {
      _text.replace(newline,re.matchedLength(),"");
      currentPos = newline; 
    }
    else currentPos = _text.length();
  }
  else
  { 
    // calculate where to split text and wrap
    int i = _text.length() * _lineClipWidth / _fm->width(_text);
    while (_fm->width(_text.left(i)) >= _lineClipWidth)
      i--;
    while (i < _text.length() && _fm->width(_text.left(i)) < _lineClipWidth)
      i++;
    currentPos = i;
    
    //check for newline character
    QRegExp re("(\r\n|\n)");
    int newline = re.indexIn(_text.left(currentPos));
    if (newline !=-1)
    {
      _text.replace(newline,re.matchedLength(),"");
      currentPos = newline; 
    }
    else //wrap text at the last space
    {
      re.setPattern("\\s");
      newline = re.lastIndexIn(_text.left(currentPos),-1);
      if(newline>0)
        currentPos = newline+1; 
    }
  }
  _currentLine = _text.left(currentPos);
  _text = _text.mid(currentPos, _text.length());

  _lineCounter++;
}

void TextElementSplitter::newPage(qreal offset)
{
  _yOffset = offset;
  _lineCounter = 0;
}

QString TextElementSplitter::currentLine() const
{
  return _currentLine;
}

void TextElementSplitter::adjustElementHeight(qreal p)
{
  _baseElementRect.moveTop(p);
}

QRectF TextElementSplitter::currentLineRect() const
{
  return _baseElementRect.translated(0, _yOffset + _baseElementRect.height()*(_lineCounter-1));
}

qreal TextElementSplitter::textBottomRelativePos() const
{
  return currentLineRect().bottom() + (_element->bottompad / 100.0) - _yOffset;
}

ORTextData *TextElementSplitter::element() const
{
  return _element;
}

bool TextElementSplitter::endOfPage() const
{
  return currentLineRect().bottom() + _baseElementRect.height() > _pageBottom;
}

bool TextElementSplitter::endOfText() const
{
  return _text.isEmpty();
}


