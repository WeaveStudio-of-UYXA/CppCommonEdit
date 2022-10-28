#pragma once
#include <QtCore>

#ifndef TRUE
#define TRUE true
#define FALSE false
#endif
namespace CE{
    enum class CELanguageName {
	    unknown = 0,
		zh_CN = 1,
		en_US = 2,
		zh_TW = 3,
    };
    static QMap<CELanguageName, QString> CEInsiderEnumtoString = {
        {CELanguageName::unknown, "unknown"},
		{CELanguageName::zh_CN, "zh_CN"},
		{CELanguageName::en_US, "en_US"},
		{CELanguageName::zh_TW, "zh_TW"}
    };
    static QMap<QString, CELanguageName> CEInverseEnumLangName = {
        {"unknown", CELanguageName::unknown},
        {"zh_CN", CELanguageName::zh_CN},
        {"en_US", CELanguageName::en_US},
        {"zh_TW", CELanguageName::zh_TW}
    };
    
    class CELanguage :public QObject {
        Q_OBJECT
    private:
        QMap<QString, QString> TransDict = {};
        QString DirPath = "";
        CELanguageName LangName = CELanguageName::unknown;
    public:
        CELanguage(CELanguageName LanguageName = CELanguageName::unknown) {
            LangName = LanguageName;
        }
        void setName(CELanguageName LanguageName) {
            LangName = LanguageName;
        }
        static CELanguageName fromStr(QString LanguageName) {
            if (CEInverseEnumLangName.keys().contains(LanguageName)) {
                return CEInverseEnumLangName[LanguageName];
            }
            else {
                return CELanguageName::unknown;
            }
        }
        void setPath(QString DirPath) {
            DirPath = DirPath;
        }
        bool load() {
            if (LangName == CELanguageName::unknown) {
                throw std::exception("Exception:CELanguage:The file could not be loaded because no effective language type was specified");
            }
			QString TargetFileName = DirPath + "/" + CEInsiderEnumtoString[LangName] + ".celang";
            QFile TargetFile;
            TargetFile.setFileName(TargetFileName);
            if (TargetFile.exists()) {
                if (TargetFile.isReadable()) {
                    TargetFile.open(QIODevice::ReadOnly | QIODevice::Text);
                    QTextStream TargetText(&TargetFile);
                    TargetText.setCodec("UTF-8");
                    while (TRUE) {
                        if (TargetText.atEnd() ) { break; }
                        QString Line = TargetText.readLine();
                        if (Line.isEmpty()) { continue; }
                        if (Line[0] != '#' && Line[0] != '\n' && Line[0] != ' ') {
                            if (!Line.contains(":")) {
                                qDebug() << "Warning:CELanguage:The separator ':' was not checked on line ' " + Line + " ' in the file:" + TargetFileName;
                                continue;
                            }
                            TransDict[Line.split(":")[0]] = Line.section(":", 0, -1);
                        }
                    }
                    TargetFile.close();
                    return TRUE;
                }
                else {
                    qDebug() << "Error:CELanguage:The specified file '" + TargetFileName + "' is unreadable";
                    return FALSE;
                }
            }
            else {
                qDebug() << "Error:CELanguage:The specified file '" + TargetFileName + "' could not be found";
                return FALSE;
            }
        }
        QString returnValueOf(QString Key) {
            if (TransDict.keys().contains(Key)) {
                return TransDict[Key];
            }
            else {
                qDebug() << "Error:CELanguage:The translated text corresponding to the key'" + Key + "' could not be found";
                return Key;
            }
        }
    };
}
