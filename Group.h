#pragma once
#include "MineSweeper.h"
#include "UnknownCells.h"
#include <algorithm>
#include <functional>
#include <iterator>

class Group
{
public:
	Group(int centerX, int centerY, int Mines);
	void printGroup();
	void addCell(int i, int j, int n);
	bool isEqual(Group &A);
	bool isContains(Group &A);
	bool isOverlap(Group &A);
	Group getOverlap(Group &A);
	void subtraction(Group &A);
	bool operator>(const Group &A) const;
	bool operator<(const Group &A) const;
	//void addCells();
	~Group() = default;
	

private:
	friend class MineSweeper;
	friend class UnknownCells;
	int Xc;
	int Yc;
	int NofM;
	std::vector<UnknownCells> UC;
};

