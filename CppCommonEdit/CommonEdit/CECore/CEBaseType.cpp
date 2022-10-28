#include "CEBaseType.h"

std::ostream& operator<<(std::ostream& os, const CE::CEInt& obj) {
	os << obj.c_get();
	return os;
}