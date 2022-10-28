#pragma once
namespace CE {
	class CEEvent 
	{
	public:
		void* From;
		void* Target;
		CEEvent() {}
		virtual void act() = 0;
	};
}
#include "qcoreevent.h"