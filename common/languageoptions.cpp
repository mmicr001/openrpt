#include <QSettings>
#include <QLocale>
#include <QApplication>
#include <QCoreApplication>
#include <QStringList>
#include <QFile>
#include <QStandardPaths>
#include <QDebug>

#include "languageoptions.h"
#include "xsqlquery.h"


#define DEBUG true

#include <QDir>

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
    qDebug() << "trying to add " << languageID << " to " << _languages;
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
  #pragma comment(linker,"/SUBSYSTEM:CONSOLE")
  qDebug() << "installLanguage()";
    QStringList content = _languages[languageID];
    qDebug() << content;

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

#if defined Q_OS_LINUX
  paths << QApplication::applicationDirPath() + "/locales";
#endif

  (void)paths.removeDuplicates();

  for (int i=0; i < paths.length(); i++)
    paths[i] = paths[i] + "/dict/";
  
  foreach (QString testDir, paths)
  {
    QFile test(testDir + file + ".qm");
    qDebug() << "test: " << test.fileName();
    if (test.exists()){
      qDebug() << "dir: " << testDir;
      qDebug() << "test: " << test.fileName();
      addTranslation(_defaultLanguage, testDir + file);
      QTranslator *ptranslator = new QTranslator;
      ptranslator->load(test.fileName());
      qApp->installTranslator(ptranslator);
    }
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
      lang.append(langAbbr );
  }

  QList<QPair<QString, QString> > transfile;
  transfile << qMakePair(QString("openrpt"), QString());
  XSqlQuery pkglist("SELECT pkghead_name, pkghead_version "
                    "  FROM pkghead"
                    " WHERE packageIsEnabled(pkghead_name);");
  while (pkglist.next())
    transfile << qMakePair(pkglist.value("pkghead_name").toString(), pkglist.value("pkghead_version").toString());

  QTranslator *translator = new QTranslator(QCoreApplication::instance());
  QPair<QString, QString> f;
  foreach (f, transfile)
  {
    foreach (QString l, lang)
    {
      qDebug() << f << " --> " << l;
      /* addTranslationToDefault((f.second.isEmpty() ? "" : f.first + "-" + f.second + "/") +
                              f.first + "." + l); */
      if (translator->load(translationFile(l, f.first, f.second)))
      {
        QCoreApplication::instance()->installTranslator(translator);
        qDebug() << "installed" << l << f.first;
        translator = new QTranslator(QCoreApplication::instance());
        break;
      }
      /* else if (f.first == "xTuple" && l == "en_us")
      {
        app.removeTranslator(QLocale::system());
        break;
      } */
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


/** @brief Find the translation file for a given locale.

    This overload should be used primarily by the Update Manager.

    Looks for the translation %file for a particular locale in all
    of the standard places xTuple ERP knows to look. The first %file
    found is returned even if it isn't the most complete, specific,
    or up-to-date.  If translation %file is found for the locale,
    this overload of translationFile(QString) tries to extract a
    version number from the translation %file and pass it back to
    the caller.

    The base translation file is expected to have a @c Version
    string in the component context. Translations from that base
    translation %file are expected to translate the @c Version
    string to something meaningful that can be put in the compatibility
    matrix. One suggestion is @c major.minor.percent-complete ,
    where @c major and @c minor are component release numbers and
    percent-complete indicates how much of the base translation
    file has been completed.

    @param[in]  localestr The locale to look for, in standard format.
    @param[in]  component The application component for which to find a
                          translation file (empty string means core)
    @param[out] version   The version string found in the translation file or
                          an empty string if none was found.

    @return The path to the translation file (may be relative or absolute)
 */
QString translationFile(QString localestr, const QString component, QString &version)
{
  QStringList paths;

  paths << QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)
        << QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);

#if defined Q_OS_MAC
  paths << QApplication::applicationDirPath() + "/../Resources";
#else
  paths << QApplication::applicationDirPath();
#endif

#if defined Q_OS_LINUX
  paths << "/usr/lib/postbooks";
#endif

  (void)paths.removeDuplicates();

  for (int i=0; i < paths.length(); i++)
    paths[i] = paths[i] + "/dict";

  QString filename = component + "." + localestr;
  QString versiondir;
  if (!version.isEmpty())
    versiondir = "/" + component + "-" + version;

  foreach (QString testDir, paths)
  {
    if (DEBUG) qDebug() << "looking for translation" << testDir << filename;

    QFile test(testDir + versiondir + "/" + filename + ".qm");
    if (test.exists())
      return testDir + versiondir + "/" + filename;
  }

  if (component=="xTuple" || component=="openrpt" || component=="reports")
    return "";

  QString dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/dict";
  QDir mkdir(dir);
  if (!mkdir.exists())
    mkdir.mkpath(dir);

  XSqlQuery data;
  data.prepare("SELECT dict_data "
               "  FROM dict "
               "  JOIN pg_class ON dict.tableoid=pg_class.oid "
               "  JOIN pg_namespace ON pg_class.relnamespace=pg_namespace.oid "
               "  JOIN lang ON dict_lang_id=lang_id "
               "  LEFT OUTER JOIN country ON dict_country_id=country_id "
               " WHERE nspname=:extension "
               "   AND lang_abbr2=:lang "
               "   AND COALESCE(country_abbr, '')=COALESCE(:country, '') "
               "   AND dict_version=:version;");
  data.bindValue(":extension", component);
  data.bindValue(":lang", localestr.split("_")[0]);
  if (localestr.contains("_"))
    data.bindValue(":country", localestr.split("_")[1].toUpper());
  data.bindValue(":version", version);
  data.exec();
  if (data.first())
  {
    QDir mkdir(dir + versiondir);
    if(!mkdir.exists())
      mkdir.mkpath(dir + versiondir);
    QFile qm(dir + versiondir + "/" + filename + ".qm");
    if (qm.open(QIODevice::WriteOnly))
      qm.write(data.value("dict_data").toByteArray());
    qm.close();

    return dir + versiondir + "/" + filename;
  }
  return "";
  /* else
  {
    QMessageBox::warning(QtCriticalMsg, 0, "Error loading QM data",
                         data, __FILE__, __LINE__);
    return "";
  } */
}
