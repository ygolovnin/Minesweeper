#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "UnknownCells.h"
#include "Group.h"
#include <algorithm>
#include <functional>
#include <map>

class MineSweeper
{
public:
	MineSweeper(int Length, int Width, int Mines);
	void SetConfig();
	void sortGroups();
	void FindNextCoords();
	~MineSweeper() = default;
private:
	int X;
	int Y;
	int NumberOfMines;
	int** Config;
	int** Numbers;
	std::vector<Group> Groups;
};

