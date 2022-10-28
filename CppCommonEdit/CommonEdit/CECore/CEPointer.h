#pragma once
#include "CECore.h"

#ifdef CE_QT_5
#include <QtCore>
#endif

namespace CE {
	class CEPointer
	{
	private:
		void* InsiderPointer;
	public :
		CEPointer(void* Pointer) {
			InsiderPointer = Pointer;
		}
	};
}
