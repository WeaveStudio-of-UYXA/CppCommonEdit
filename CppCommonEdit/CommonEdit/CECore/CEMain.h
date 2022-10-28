#pragma once
#include <QtCore>
#include <QApplication>
#include "CEObject.h"
#include "../CEFunction/CELanguage.h"
#include "../CEFunction/CESettings.h"
#include <map>
#include <string>

#define def_CEMain class Main : public CE::CEMain{public:Main(int argc, char* argv[]):CEMain(argc, argv) {};
#define do_CEMain int main(int argc, char* argv[]){Main app(argc, argv); app.act(); return 0;}
#define def_END }; do_CEMain
#define CEMainPara int argc, char* argv[]
namespace CE {
	class CEMain :public CEObject
	{
		
		Public std::map<std::string, std::string> SetDict;
		Private int gargc;
		Private char** gargv;
		Public CEMain(int argc, char* argv[]) {
			std::cout << "开始构造主类" << std::endl;
			ObjectType = "Main";
			InstanceName = "Main";
			regType(CE::CEMain);
			gargc = argc;
			gargv = argv;
		}
		Public void act() {
			doPreSet();
			std::cout << "开始执行主函数" << std::endl;
			main(gargc, gargv);
			std::cout << "主函数执行完毕" << std::endl;
		}
		Public virtual void doPreSet() = 0;
		Public virtual int main(CEMainPara) = 0;
		Public ~CEMain() {
			std::cout << "主类执行完毕" << std::endl;
		}
	};
}

namespace Model
{
	class Model
	{
		Public virtual void cal() = 0;
		Public enum class Type{
			Model1 = 1,
			Model2 = 2,
		};
	};
	class Model1 :public Model
	{
		Public void cal() {		}
	};
	class Model2 :public Model
	{
		Public void cal() {    }
	};
	class CAL
	{
		Public Model* m;
		Public CAL(Model::Type model) {
			switch (model)
			{
			case Model::Type::Model1:
				m = new Model1();
				break;
			case Model::Type::Model2:
				m = new Model2();
				break;
			default:
				break;
			}
		}
	};
}
