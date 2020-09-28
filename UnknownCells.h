#pragma once
#include "MineSweeper.h"
#include "Group.h"

class UnknownCells {
public:
	UnknownCells(int x, int y, int n);
	bool operator>(const UnknownCells &U) const;
	bool operator<(const UnknownCells &U) const;
	bool operator==(const UnknownCells &U) const;
	~UnknownCells () = default;

private:
	friend class MineSweeper;
	friend class Group;
	int X;
	int Y;
	int Number;
};


