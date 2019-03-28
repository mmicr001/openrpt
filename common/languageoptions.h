#ifndef LANGUAGEOPTIONS_H
#define LANGUAGEOPTIONS_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QTranslator>

class LanguageOptions : public QObject
{
	Q_OBJECT

public:
	LanguageOptions(QObject *parent);
	~LanguageOptions();

private:
	
public:
	void addLanguage(QString languageID, QString languageTitle);
	void addTranslation(QString languageID, QString translationFile);
	void addTranslationToDefault(QString file);
	void select(QString languageID);
	void installLanguage(QString languageID);
	void installSelected(void);
        void login();
	QStringList languageTitlesList(void);
	QString selectedTitle();
	void selectFromTitle(QString title);
	
private:
	QString _defaultLanguage;
	QString _selectedLanguage;
	QMap<QString,QStringList> _languages;
	QList<QTranslator *> _translators;
public:
};

QString translationFile(const QString localestr, const QString component, QString &version);

#endif // LANGUAGEOPTIONS_H
