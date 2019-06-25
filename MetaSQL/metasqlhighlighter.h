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

#ifndef METASQLHIGHLIGHTER_H
#define METASQLHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class QColor;
class QTextDocument;
class QTextEdit;

class MetaSQLHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT

  public:
    MetaSQLHighlighter(QObject *parent);
    MetaSQLHighlighter(QTextDocument *document);
    MetaSQLHighlighter(QTextEdit *editor);
    ~MetaSQLHighlighter();

  protected:
    enum State { NormalState = -1, InsideCStyleComment, InsideString, InsideMetaSQL, InsideMetaSQLString };
    virtual void highlightBlock(const QString &text);

    QColor       _commentColor;
    QColor       _errorColor;
    QColor       _extensionColor;
    QColor       _keywordColor;
    QColor       _literalColor;

  private:
    virtual void init();

    QRegExp _kwtest;
    QRegExp _extest;
    QRegExp _numerictest;
    QRegExp _wordtest;
    QRegExp _metasqlquotetest;
    QRegExp _sqlquotetest;

};

#endif // METASQLHIGHLIGHTER_H
