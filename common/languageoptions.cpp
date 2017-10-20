#include <QSettings>
#include <QLocale>
#include <QApplication>
#include <QStringList>
#include <QFile>
#include <QStandardPaths>

#include "languageoptions.h"
#include "xsqlquery.h"


LanguageOptions::LanguageOptions(QObject *parent)
    : QObject(parent)
{
    _defaultLanguage = "Default";
    addLanguage(_defaultLanguage, _defaultLanguage);

    QSettings settings(QSettings::UserScope, "OpenMFG.com", "OpenRPT");
    _selectedLanguage = settings.value("/OpenRPT/_selectedLanguage", _defaultLanguage).toString();

    addLanguage("en", "English");

    QLocale sysl = QLocale::system();
    if (sysl.language() != QLocale::C && sysl.language() != QLocale::English)
      addTranslationToDefault("openrpt." + sysl.name().toLower());
}



LanguageOptions::~LanguageOptions()
{
}


void LanguageOptions::addLanguage(QString languageID, QString languageTitle)
{
    if(_languages.contains(languageID)) 
    {
        return;
    }

    QStringList content;
    content << languageTitle;
    _languages.insert(languageID,content);
}



void LanguageOptions::addTranslation(QString languageID, QString translationFile)
{
    if(_languages.contains(languageID)) 
    {
        _languages[languageID] << translationFile;
    }    
}


void LanguageOptions::select(QString languageID)
{
    _selectedLanguage = languageID;

    QSettings settings(QSettings::UserScope, "OpenMFG.com", "OpenRPT");
    settings.setValue("/OpenRPT/_selectedLanguage", _selectedLanguage);
}



void LanguageOptions::installLanguage(QString languageID)
{
    QStringList content = _languages[languageID];

    for (int i=1; i<content.size(); i++) 
    {
        QTranslator *ptranslator = new QTranslator;
        ptranslator->load(content[i]);
        qApp->installTranslator(ptranslator);
    }

    // translation for Default title (can't do it before because the translations are not loaded)
    _languages[_defaultLanguage][0] = tr("Default");
}



void LanguageOptions::installSelected(void)

{
    installLanguage(_selectedLanguage);
}



void LanguageOptions::addTranslationToDefault(QString file)

{
  QStringList paths;

  paths << QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)
        << QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);

#if defined Q_OS_MAC
  paths << QApplication::applicationDirPath() + "/../Resources";
#else
  paths << QApplication::applicationDirPath();
#endif

  (void)paths.removeDuplicates();

  for (int i=0; i < paths.length(); i++)
    paths[i] = paths[i] + "/dict";

  foreach (QString testDir, paths)
  {
    QFile test(testDir + file + ".qm");
    if (test.exists())
      addTranslation(_defaultLanguage, testDir + file);
  }
}

void LanguageOptions::login()
{
  QStringList lang;
  if (_languages[_defaultLanguage].length() > 1)
  {
    lang << _languages[_defaultLanguage][1].mid(8);
    _languages[_defaultLanguage].removeLast();
  }

  XSqlQuery langq("SELECT lang_abbr2,   lang_qt_number,"
                  "       country_abbr, country_qt_number"
                  "  FROM usr"
                  "  JOIN locale  ON usr_locale_id     = locale_id"
                  "  JOIN lang    ON locale_lang_id    = lang_id"
                  "  LEFT OUTER JOIN country ON locale_country_id = country_id"
                  " WHERE usr_username = getEffectiveXtUser();");
  if (langq.first())
  {
    QString langAbbr    = langq.value("lang_abbr2").toString();
    QString countryAbbr = langq.value("country_abbr").toString().toUpper();

    if (! langAbbr.isEmpty() && ! countryAbbr.isEmpty())
      lang.append(langAbbr + "_" + countryAbbr.toLower());
    else if (! langAbbr.isEmpty())
      lang.append(langAbbr + "_" + countryAbbr.toLower());
  }

  QList<QPair<QString, QString> > transfile;
  transfile << qMakePair(QString("openrpt"), QString());
  XSqlQuery pkglist("SELECT pkghead_name, pkghead_version "
                    "  FROM pkghead"
                    " WHERE packageIsEnabled(pkghead_name);");
  while (pkglist.next())
    transfile << qMakePair(pkglist.value("pkghead_name").toString(), pkglist.value("pkghead_version").toString());

  QPair<QString, QString> f;
  foreach (f, transfile)
  {
    foreach (QString l, lang)
    {
      addTranslationToDefault((f.second.isEmpty() ? "" : f.first + "-" + f.second + "/") +
                              f.first + "." + l);
    }
  }
}

QStringList LanguageOptions::languageTitlesList(void)
{
    QStringList res;

    foreach (QStringList value, _languages) 
    {
        res << value[0];
    }

    return res;
}


QString LanguageOptions::selectedTitle()
{
    return _languages.value(_selectedLanguage)[0];

}


void LanguageOptions::selectFromTitle(QString title)
{
    QString id = _defaultLanguage;

    QMapIterator<QString,QStringList> i(_languages);

     while (i.hasNext()) 
    {
         i.next();
        QString currentTitle = i.value()[0];
        if(currentTitle==title) {
            id = i.key();
            break;
        }
    }

    select(id);
}

