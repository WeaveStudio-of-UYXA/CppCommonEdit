#include <QtWidgets>
#include <QApplication>
#include "CommonEdit/CommonEdit.h"
#include <iostream>
class B :public CE::CEObject
{
    
    Public B(CE::CEObject* parent = CE_NULLPTR) {
        ObjectType = "B";
        this->setParent(parent);
    }
};

class A :public CE::CEObject
{
    Public B* b;
    Public A(CE::CEObject* parent = CE_NULLPTR) {
        ObjectType = "A";
        this->setParent(parent);
        b = new B(this);
    }
    Public void reg() {
        regPIns(b);
        regChild;
    }
};


def_CEMain
    Public A* a1;
    Public void doPreSet() {
        None
    }
    Public CE::CEInt num = 9;
    Public int main(CEMainPara) {
        qDebug() << "CE Hello World";
        QApplication a(argc, argv);
        CE::CEList<int> test = {1,2,3};
        qDebug() << test.toQString();
        num.setParent(this);
        regIns(num);
        std::cout << num + 10 << std::endl;
        std::cout << "num的实例名称是"+num.InstanceName.get() << std::endl;
        std::cout << "num的类型是"+num.objectType() << std::endl;
        a1 = new A(this);
        this->reg();
        std::cout <<"b实例的全程名为："+ a1->b->InstanceName.get() << std::endl;

        
        return 0;
        //return a.exec();
    }
    Public void reg() {
        
        regPIns(a1);
        regChild;
    }
def_END

//CE::CEVisualNovelWidget* win = new CE::CEVisualNovelWidget();
//CE::CEQueueFuncTest testFunc;
//qDebug() << CE::CEScripts::calculator<float>("((10+20)*2)*-2");
/*
        qDebug() << test.toQString();
        qDebug() << test.at(-1);
        qDebug() << test.at(-2);
        qDebug() << test.at(-3);
        test.append(4);
        qDebug() << test.toQString();
        qDebug() << test.length();
        qDebug() << test.at(3);
        test.insert(1, -2);
        qDebug() << test.toQString();
        test.remove(0);
        qDebug() << test.toQString();
        test.clear();
        qDebug() << test.toQString();
        test.append(222);
*/



