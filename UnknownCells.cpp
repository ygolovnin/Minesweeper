#include "UnknownCells.h"

UnknownCells::UnknownCells(int x, int y, int n) {
	X = x;
	Y = y;
	Number = n;
}

bool UnknownCells::operator<(const UnknownCells &U) const {
	if (this->Number < U.Number) {
		return true;
	}
	return false;
}

bool UnknownCells::operator>(const UnknownCells &U) const {
	if (this->Number > U.Number) {
		return true;
	}
	return false;
}

bool UnknownCells::operator==(const UnknownCells &U) const {
	if (this->Number == U.Number) {
		return true;
	}
	return false;
}