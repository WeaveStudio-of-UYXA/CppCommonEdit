#pragma once
#include <QtCore>
namespace CE {
	class CEScripts {
    public:
        template<typename T>static T calculator(QString Exp) {
            int level = 0;
            int start;
            QList<QStringList> ans;
            QString sig;
            QList<QChar> ope;
            QList<QString> spl;
            ope = { '+','-','*','/','^' };
            for (int i = 0; i < Exp.length(); i++) {
                QChar Cur = Exp[i];
                if (Cur == '(') {
                    if (level == 0) { start = i; }
                    level++;
                }
                else if (Cur == ')') {
                    level--;
                    if (level == 0) {
                        ans.append({ Exp.mid(start, i - start + 1), QString::number(calculator<T>(Exp.mid(start + 1, i - start - 1))) });
                    }
                }
            }
            for (int i = 0; i < ans.length(); i++) {
                Exp.replace(ans[i][0], ans[i][1]);
            }
            for (int i = 0; i < Exp.length(); i++) {
                QChar Cur = Exp[i];
                if (ope.contains(Cur)) {
                    if (sig == "" && Cur == '-') {
                        sig.append("-");
                    }
                    else {
                        spl.append(sig);
                        spl.append(Cur);
                        sig.clear();
                    }
                }
                else {
                    sig.append(Cur);
                }
            }
            spl.append(sig);
            qDebug() << spl;
            for (int i = 1; i < spl.length(); i += 2) {
                if (spl[i] == "^") {
                    spl[i + 1] = QString::number(pow(spl[i - 1].toInt(),spl[i + 1].toInt()-1));
                    spl[i] = "*";
                }
            }
            for (int i = 1; i < spl.length(); i += 2) {
                if (spl[i] == "*") {
                    spl[i + 1] = QString::number(spl[i - 1].toFloat() * spl[i + 1].toFloat());
                    spl[i - 1] = "0";
                    spl[i] = "+";
                }
                else if (spl[i] == "/") {
                    spl[i + 1] = QString::number(spl[i - 1].toFloat() / spl[i + 1].toFloat());
                    spl[i - 1] = "0";
                    spl[i] = "+";
                }
            }
            T fa = spl[0].toFloat();
            for (int i = 1; i < spl.length(); i += 2) {
                if (spl[i] == "+") {
                    fa += spl[i + 1].toFloat();
                }
                else {
                    fa -= spl[i + 1].toFloat();
                }
            }
            return fa;
        }
	};
}