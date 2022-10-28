#pragma once
#include <QtCore>
#include "CEMacro.h"
#include "../CEFunction/CEOperate.h"

#ifndef CE_DYNAMIC_AND_QUEUE_FUNC_FRAMEWORK
#define CE_DYNAMIC_AND_QUEUE_FUNC_FRAMEWORK
#define CE_DYNAMIC Q_OBJECT public :CE::CEQueueFunc CEDynamicFuncQueue; public slots: void doCEDynamicFunc(){CEDynamicFuncQueue.doFunc();} void doCEDynamicFuncFirst(){CEDynamicFuncQueue.doFunc(CE::CEQueueFuncPolicy::First);}void doCEDynamicFuncWith(CEDynamicFunctionID ID){CEDynamicFuncQueue.doFunc(ID);}
#define CE_Return return
#define enableCEDynamicFunc public QObject, public CE::CEQueueFuncBase
#define CEDF_VOID {}
#define CEDF_BothVOID {},{}
#define CEDF_ReturnVOID {CE::CEQueueReturnThen::next,CEDF_BothVOID}
#define CEDF_ReturnREMOVE {CE::CEQueueReturnThen::remove,CEDF_BothVOID}
#define CEDF_ReturnREDO {CE::CEQueueReturnThen::redo,CEDF_BothVOID}
#define CEDF_ReturnCYCLE {CE::CEQueueReturnThen::cycle,CEDF_NormalList,CEDF_PointerList}
#define CEDF_ReturnEDIT {CE::CEQueueReturnThen::edit,CEDF_NormalList,CEDF_PointerList}
#define CEDF_ReturnStruct CE::CEQueueReturnInfo
#define CEDF_ParaLists QCENormalList CEDF_NormalList, QCEPointerList CEDF_PointerList
#define CEDF_FuncInfo CE::CEQueueFuncInfo CEDF_FunctionInfo
#define CEDF_slot CEDF_ReturnStruct dynamicFunc(CEDF_FuncInfo)
#define ifIsCEDF(funcName) if(CEDF_FunctionInfo.FuncName==#funcName){ CEDF_ReturnStruct ReturnInfo = this->funcName(CEDF_FunctionInfo.NormalParaList,CEDF_FunctionInfo.PointerParaList);CE_Return ReturnInfo;}
#define addCEDF(funcName,Normal,Pointer) this->CEDynamicFuncQueue.addDynamicFunc(this,{#funcName,Normal,Pointer});
#define removeCEDF(CEDF_ID) this->CEDynamicFuncQueue.removeDynamicFunc(CEDF_ID);
#define CEDF_doFunc doCEDynamicFunc
#define CEDF_def(funcName) public: CEDF_ReturnStruct funcName(CEDF_ParaLists)
#define CEDF_toQtSlot(CEDFName,newName) public slots: void newName(CEDF_ParaLists,bool QtSlots){CEDF_ReturnStruct Return = CEDFName(CEDF_NormalList,CEDF_PointerList);}
#define CEDF_asQtSlot true;
typedef long long CEDynamicFunctionID;
typedef QStringList QCENormalList;
typedef QList<void*> QCEPointerList;
#endif

namespace CE {
	enum class CEQueueFuncPolicy
	{
		unknown = 0,
		First = 1,
		Traverse = 2,
	};
	struct CEQueueFuncInfo {
		QString FuncName;
		QStringList NormalParaList;
		QList<void*> PointerParaList;
	};
	enum class CEQueueReturnThen 
	{
		redo = 1,
		remove = 2,
		break_ = 3,
		next = 4,
		edit = 5,
		cycle = 6,
	};
	struct CEQueueReturnInfo {
		CEQueueReturnThen Next;
		QStringList NormalReturnList;
		QList<void*> PointerReturnList;
	};
	class CEQueueFuncBase
	{
	public:
		virtual CEQueueReturnInfo dynamicFunc(CEQueueFuncInfo dynamic) = 0;
	};
	class CEQueueFunc :public QObject
	{
		Q_OBJECT
	signals:
		void queueIsEmptied();
	private:
		QQueue<CEQueueFuncInfo> InsiderFuncQueue;
		QQueue<CEQueueFuncBase*> InsiderTargetQueue;
		QQueue<CEDynamicFunctionID> InsiderDynamicID;
	public: 
		CEQueueFunc(QObject* parent = Q_NULLPTR) {
			INIT_RAND_SEED;
			this->setParent(parent);
		}
		CEDynamicFunctionID addDynamicFunc(CEQueueFuncBase* target, CEQueueFuncInfo Info) {
			QDateTime current_date_time = QDateTime::currentDateTime();
			CEDynamicFunctionID FunctionID = (QString::number(current_date_time.toTime_t()) +QString::number(CE::CEOperate::randInt(10000000,99999999))).toLongLong();
			InsiderTargetQueue.append(target);
			InsiderFuncQueue.append(Info);
			InsiderDynamicID.append(FunctionID);
			return FunctionID;
		}
		bool removeDynamicFunc(CEDynamicFunctionID FunctionID) {
			for (int i = 0; i < InsiderDynamicID.length(); i++) {
				if (InsiderDynamicID[0] == FunctionID) {
					InsiderTargetQueue.removeAt(i);
					InsiderFuncQueue.removeAt(i);
					InsiderDynamicID.removeAt(i);
					return TRUE;
				}
			}
			return FALSE;
		}
	public slots:
		void doFunc(CEQueueFuncPolicy FuncPolicy = CEQueueFuncPolicy::Traverse) {
			unsigned long long RAWLength = InsiderFuncQueue.length();
			if (RAWLength == 0) { 
				if (InsiderFuncQueue.isEmpty()) {
					emit queueIsEmptied();
				}
				return; 
			}
			QList<int> removeIndex;
			CEQueueReturnInfo Info;
			switch (FuncPolicy) {
			case CEQueueFuncPolicy::Traverse:
				for (unsigned long long i = 0; i < RAWLength; i++) {
					while (true) {
						Info = InsiderTargetQueue[i]->dynamicFunc(InsiderFuncQueue[i]);
						if (Info.Next == CEQueueReturnThen::break_ || Info.Next == CEQueueReturnThen::next) {
							break;
						}
						else if (Info.Next == CEQueueReturnThen::remove) {
							removeIndex.append(i);
							break;
						}
						else if (Info.Next == CEQueueReturnThen::redo) {
							None;
						}
						else if (Info.Next == CEQueueReturnThen::cycle) {
							InsiderFuncQueue[i].NormalParaList = Info.NormalReturnList;
							InsiderFuncQueue[i].PointerParaList = Info.PointerReturnList;
						}
						else if (Info.Next == CEQueueReturnThen::edit) {
							InsiderFuncQueue[i].NormalParaList = Info.NormalReturnList;
							InsiderFuncQueue[i].PointerParaList = Info.PointerReturnList;
							break;
						}	
					}
					if (Info.Next == CEQueueReturnThen::break_) {
						break;
					}
				}
				for (int i = 0; i < removeIndex.length(); i++) {
					InsiderFuncQueue.removeAt(removeIndex[i] - i);
					InsiderTargetQueue.removeAt(removeIndex[i] - i);
					InsiderDynamicID.removeAt(removeIndex[i] - i);
				}
				break;
			case CEQueueFuncPolicy::First:
				while (true) {
					Info = InsiderTargetQueue[0]->dynamicFunc(InsiderFuncQueue[0]);
					if (Info.Next == CEQueueReturnThen::break_ || Info.Next == CEQueueReturnThen::next) {
						break;
					}
					else if (Info.Next == CEQueueReturnThen::remove) {
						removeIndex.append(0);
						break;
					}
					else if (Info.Next == CEQueueReturnThen::redo) {

					}
					else if (Info.Next == CEQueueReturnThen::edit) {
						InsiderFuncQueue[0].NormalParaList = Info.NormalReturnList;
						InsiderFuncQueue[0].PointerParaList = Info.PointerReturnList;
						break;
					}
				}
				for (int i = 0; i < removeIndex.length(); i++) {
					InsiderFuncQueue.removeAt(removeIndex[i] - i);
					InsiderTargetQueue.removeAt(removeIndex[i] - i);
					InsiderDynamicID.removeAt(removeIndex[i] - i);
				}
				break;
			}
			if (InsiderFuncQueue.isEmpty()) {
				emit queueIsEmptied();
			}
		}
		bool doFunc(CEDynamicFunctionID FunctionID) {
			unsigned long long RAWLength = InsiderFuncQueue.length();
			if (RAWLength == 0) {
				if (InsiderFuncQueue.isEmpty()) {
					emit queueIsEmptied();
				}
				return FALSE; 
			}
			QList<int> removeIndex;
			CEQueueReturnInfo Info;
			for (unsigned long long i = 0; i < RAWLength; i++) {
				if (InsiderDynamicID[i]==FunctionID) {
					while (TRUE) {
						Info = InsiderTargetQueue[i]->dynamicFunc(InsiderFuncQueue[i]);
						if (Info.Next == CEQueueReturnThen::break_ || Info.Next == CEQueueReturnThen::next) {
							break;
						}
						else if (Info.Next == CEQueueReturnThen::remove) {
							removeIndex.append(i);
							break;
						}
						else if (Info.Next == CEQueueReturnThen::redo) {

						}
						else if (Info.Next == CEQueueReturnThen::edit) {
							InsiderFuncQueue[i].NormalParaList = Info.NormalReturnList;
							InsiderFuncQueue[i].PointerParaList = Info.PointerReturnList;
							break;
						}
					}
					for (int i = 0; i < removeIndex.length(); i++) {
						InsiderFuncQueue.removeAt(removeIndex[i] - i);
						InsiderTargetQueue.removeAt(removeIndex[i] - i);
						InsiderDynamicID.removeAt(removeIndex[i] - i);
					}
					if (InsiderFuncQueue.isEmpty()) {
						emit queueIsEmptied();
					}
					return TRUE;
				}
			}
			return FALSE;
		}
	};

	class CEQueueFuncTest : enableCEDynamicFunc
	{
		CE_DYNAMIC
	public:
		CEQueueFuncTest() {
			qDebug()<<addCEDF(Func1, { "30" }, CEDF_VOID);
			qDebug()<<addCEDF(Func2, CEDF_BothVOID);
			doCEDynamicFunc();
			doCEDynamicFunc();
		}
		CEDF_def(Func1) {
			qDebug() << CEDF_NormalList[0];
			CEDF_NormalList[0] = QString::number(CEDF_NormalList[0].toInt() - 1);
			if (CEDF_NormalList[0] != "0") {
				CE_Return CEDF_ReturnCYCLE;
			}
			else {
				CE_Return CEDF_ReturnREMOVE;
			}
		};
		CEDF_toQtSlot(Func1,qFunc1);
		CEDF_def(Func2) {
			qDebug() << "FUNC2";
			CE_Return CEDF_ReturnVOID;
		};
		CEDF_slot{
			ifIsCEDF(Func1);
			ifIsCEDF(Func2);
		}
	};
}