#pragma once
//CEOBJECT
#include "CEMacro.h"
#include <string>
#include <list>
#include <iostream>
#include <queue>
#define regIns(CEObjectInstance) CEObjectInstance.setInstanceName(#CEObjectInstance);std::cout<<"注册"+this->InstanceName.get()+"的子对象"+CEObjectInstance.InstanceName.get()+"完毕"<<std::endl
#define regPIns(CEObjectInstance) CEObjectInstance->setInstanceName(#CEObjectInstance);std::cout<<"注册"+this->InstanceName.get()+"的子对象"+CEObjectInstance->InstanceName.get()+"完毕"<<std::endl
#define regType(CEObjectName) ObjectType = #CEObjectName
#define CEVarB(Type) CE::CEFieldObject<Type>
#define CEVar(Type) CE::CEField<Type>
#define CEType(Type) CE::CEField<Type>
#define CETypeB(Type) CE::CEFieldObject<Type>
#define regChild for (auto i = children.begin(); i != children.end(); i++) { if (*i != CE_NULLPTR){std::cout <<"开始执行"+this->InstanceName.get()+"的子对象" + (*i)->InstanceName.get() +"的注册函数：" << std::endl;(*i)->reg();std::cout <<this->InstanceName.get()+"的子对象" + (*i)->InstanceName.get() +"的注册函数执行完毕\n" << std::endl;}}
namespace CE {
	template<typename T> class CEFieldObject
	{
		Public T value;
		Public CEFieldObject() {}
		Public CEFieldObject(T v) { value = v; }
		Public void set(T v) { value = v; }
		Public T get(void) { return value; }
		Public T c_get(void) const { return value; }
		Public operator T(void) { return value; }
		Public void operator=(T v) { value = v; }
	};
	class CEObject 
	{
		Protected std::string ObjectType;
		Protected CEObject* parent = CE_NULLPTR;
		Public std::list<CEObject*> children = { };
		Public CEObject() {
			regType(CE::CEObject);
		};
		Public CEVarB(std::string) ObjectName;
		Public CEVarB(std::string) InstanceName;
		Public void setParent(CEObject* p) {
			parent = p;
			if (p != CE_NULLPTR) {
				p->children.push_back(this);
			}
		}
		Public void removeChild(CEObject* c) {
		if (c != CE_NULLPTR) {
				children.remove(c);
			}
		}
		Public ~CEObject() {
			std::cout << this->InstanceName.get() + "执行析构" << std::endl;
			if (parent != CE_NULLPTR) {
				parent->removeChild(this);
			}
			auto i = children.begin();
			while(children.size()!= 0) {
				if (*i != CE_NULLPTR) {
					delete (*i);	
				}
				if (children.size() != 0) { children.pop_front(); }
				else { break; }
			}
			std::cout << this->InstanceName.get() + "完成析构" << std::endl;
		}
		Public void setInstanceName(std::string insName) {
			if (parent == CE_NULLPTR) {
				this->InstanceName.set(insName);
			}else{
				this->InstanceName.set(parent->InstanceName.get() + "::" + insName);
			}
		}
		Public std::string objectType(void) {
			return ObjectType;
		}
		Public virtual void reg() {};
		/*Public std::string getFullName() {
			std::string f = "";
			if (parent != CE_NULLPTR) {
				f.append(std::string("::")+parent.get()->getFullName());
				return f;
			}
			else {
				return InstanceName.get();
			}
		}*/
	};
	template<typename T> class CEField :public CEFieldObject<T>, public CEObject
	{
		Public CEField(T value) :CEFieldObject<T>(value), CEObject() {
			regType(CE::CEField<T>);
		}
	};
}

