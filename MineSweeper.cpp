#include "MineSweeper.h"
#define DEBUGs



MineSweeper::MineSweeper(int Length, int Width, int Mines) {
	X = Length;
	Y = Width;
	NumberOfMines = Mines;

}

void MineSweeper::SetConfig() {
	
	int** Config = new int*[X];
	for (int i = 0; i < X; ++i) {
		Config[i] = new int[Y];
	}

	int** Numbers = new int*[X];
	for (int i = 0; i < X; ++i) {
		Numbers[i] = new int[Y];
	}

	std::string s;
	std::ifstream file("field.txt");
	std::vector<int> tmp;
	int k = 0;
	for (int i = 0; i < Y; ++i) {
#ifdef DEBUG
		std::cout << "i= " << i << std::endl;
#endif //DEBUG
		getline(file, s);
		//std::cin >> s;
#ifdef DEBUG
		std::cout << "s= " << s << std::endl;
#endif // DEBUG
		int j = 0;
		for (auto ex : s) {
#ifdef DEBUG
		std::cout << "j = " << j << std::endl;
		std::cout << "ex = " << ex << std::endl;
#endif // DEBUG
			if (isdigit(ex)) {
				Config[i][j] = atoi(&ex);
#ifdef DEBUG
				std::cout << "k = " << k << std::endl;
#endif // DEBUG
				if (Config[i][j] != 0) {
					Group temp_group(i, j, Config[i][j]);
					this->Groups.push_back(temp_group);
				}
			}
			else {
				Config[i][j] = -1;
#ifdef DEBUG
				std::cout << "k = " << k << std::endl;
#endif // DEBUG	
			}
			Numbers[i][j] = k;
			k++;
			++j;
		}

	}
#ifdef DEBUG
	std::cout << "numbers = " << std::endl;
	for (int i = 0; i < Y; ++i) {
		for (int j = 0; j < X; ++j) {
			std::cout << Numbers[i][j] << " ";
		}
		std::cout << std::endl;
	}
#endif // DEBUG

	for (auto &g : this->Groups) {
		for (int i = g.Xc - 1; i <= g.Xc + 1; ++i) {
			for (int j = g.Yc - 1; j <= g.Yc + 1; ++j) {
				if ((i >= 0) && (i < X) && (j >= 0) && (j < Y) && (i != g.Xc || j != g.Yc) && (Config[i][j] == -1)) {
					g.addCell(i, j, Numbers[i][j]);
					//std::cout << "size" << g.UC.size() << std::endl;
				}
			}
		}
	}

#ifdef DEBUG
	for (auto &g : this->Groups) {
		g.printGroup();
	}
	sortGroups();
	std::cout << "this->Groups.size() = " << this->Groups.size() << std::endl;
	for (auto &g : this->Groups) {
		g.printGroup();
	}
	bool res = this->Groups[0].isEqual(this->Groups[0]);
	std::cout << "TEST" << std::endl;
	bool res1 = this->Groups[2] > this->Groups[0];
	bool res2 = this->Groups[0] > this->Groups[0];
	std::cout << "res, res1, res2 = " << res << ", " << res1 << ", " << res2 << std::endl;
	std::sort(this->Groups.begin(), this->Groups.end());

	for (int i = 0; i < Y; ++i) {
		for (int j = 0; j < X; ++j) {
			std::cout << Config[i][j] << " ";
		}
		std::cout << std::endl;
	}
#endif // DEBUG

	return;
}

void MineSweeper::sortGroups() {
	std::sort(this->Groups.begin(), this->Groups.end(), std::greater<Group>());
	for (auto &g : this->Groups) {
		std::sort(g.UC.begin(), g.UC.end());
	}
}

void MineSweeper::FindNextCoords() {
	if (this->Groups.size() == 0) {
		std::cout << 0 << ", " << 0 << std::endl;
		return;
	}
	//groups algorithm 
	bool res;
	int counter = this->Groups.size();
	do {
		res = false;
		sortGroups();
#ifdef DEBUG
		for (auto &g : this->Groups) {
			g.printGroup();
		}
		system("pause");
#endif // DEBUG
		for (int i = 0; i < this->Groups.size() - 1; ++i) {
			Group groupI = this->Groups[i];
			for (int j = i + 1; j < this->Groups.size(); ++j) {
				Group groupJ = this->Groups[j];
				if (groupI.isEqual(groupJ)) {
					Groups.erase(Groups.begin() + (j - 1));
					break;
					//std::cout << "ERASE GROUP" << std::endl;
				}
				Group big = groupJ;
				Group small = groupI;
				if (groupI.UC.size() > groupJ.UC.size()) {
					big = groupI;
					small = groupJ;
				}

				if (big.isContains(small)) {
					big.subtraction(small);
					res = true;
				}
				else if (groupI.isOverlap(groupJ)) {
#ifdef DEBUG
					std::cout << "groupI.NofM = " << groupI.NofM << ", groupJ.NofM= " << groupJ.NofM << std::endl;
#endif // DEBUG
					if (groupI.NofM >= groupJ.NofM) {
						big = groupI;
						small = groupJ;
					}
					else {
						big = groupJ;
						small = groupI;
						//std::cout << "here" << std::endl;
					}
#ifdef DEBUG
					std::cout << "big:" << std::endl;
					big.printGroup();
					std::cout << "small:" << std::endl;
					small.printGroup();
#endif // DEBUG
					Group overlap = big.getOverlap(small);
#ifdef DEBUG
					std::cout << "overlap:" << std::endl;
					overlap.printGroup();
#endif // DEBUG
					if ((overlap.NofM == overlap.UC.size()) || (overlap.NofM == 0)) {
						this->Groups.push_back(overlap);
						big.subtraction(overlap);
						small.subtraction(overlap);
						res = true;
					}
					
				}
				
			}
#ifdef DEBUG
			std::cout << "this->Groups.size() = " << this->Groups.size() << std::endl;
			system("pause");
#endif // DEBUG
		}
#ifdef DEBUG
		std::cout << "counter = " << counter << ", Groups.size() = " << this->Groups.size() << std::endl;
		system("pause");
#endif // DEBUG

		if (counter == this->Groups.size()) {
			res = false;
		}
		else {
			counter = this->Groups.size();
		}
	} while (res);


	for (int i = this->Groups.size() - 1; i >= 0; --i) {
		//std::cout << Groups[i].NofM << std::endl;
		if ((this->Groups[i].NofM) == 0) {
			//std::cout << "ANSWER:" << std::endl;
			std::cout << this->Groups[i].UC[0].X << ", " << this->Groups[i].UC[0].Y << std::endl;
			return;
		}
	}
	
	//probabilities
	std::map<UnknownCells, double> Probabilities;
	for (auto group : this->Groups) {
		for (auto cell : group.UC) {
			double val;
			if (Probabilities.find(cell) == Probabilities.end()) {
				val = (double)group.NofM / group.UC.size();
				Probabilities.emplace(cell, val);
			}
			else {
				val = 1 - (1 - Probabilities.at(cell)) * (1 - (double)group.NofM / group.UC.size());
				Probabilities.emplace(cell, val);
			}
		}
	}
	double PE = 1000;
	UnknownCells a = this->Groups[0].UC[0];
	for (auto &p : Probabilities) {
		//std::cout << "prob = " << p.second << std::endl;
		if (p.second < PE) {
			a = p.first;
		}
	}
	std::cout << "ANSWER: ";
	std::cout << a.X << ", " << a.Y << std::endl;

	return;
}



