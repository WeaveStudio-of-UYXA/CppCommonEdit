#pragma once
#include "CEObject.h"
#include "CEMacro.h"

#include <string>
#include <list>

namespace CE {
	class CEInt :public CEField<int>
	{
		Public CEInt(int value) :CEField<int>(value) {
			regType(CE::CEInt);
		}
	};
}

std::ostream& operator<<(std::ostream& os, const CE::CEInt& obj);