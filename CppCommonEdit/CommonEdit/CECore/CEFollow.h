#pragma once
#include <string>
#include <map>
#include <list>
#include "../CECore/CECore.h"

#define __init__(ObjectName) private: std::string CE_OBJECTNAME = #ObjectName;public: ObjectName
namespace CE
{
	class CEBaseObject
	{
		__init__(CEBaseObject)(CEBaseObject* parent = CE_NULLPTR) {
			
		}
	};
}