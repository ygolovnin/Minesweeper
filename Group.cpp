#include "Group.h"
#define DEBUGs

Group::Group(int centerX, int centerY, int Mines) {
	Xc = centerX;
	Yc = centerY;
	NofM = Mines;
}

void Group::addCell(int i, int j, int n) {
	UnknownCells tmp(i, j, n);
	this->UC.push_back(tmp);
}

bool Group::isEqual(Group &A) {
	if (this->NofM != A.NofM) {
		return false;
	}
	if (this->UC.size() != A.UC.size()) {
		return false;
	}
	for (int i = 0; i < this->UC.size(); ++i) {
		if (this->UC[i].Number != A.UC[i].Number) {
			return false;
		}
	}
	return true;
}

void Group::printGroup() {
	std::cout << "Xc = " << Xc << ", Yc = " << Yc << ", Mines = " << NofM << std::endl;
	std::cout << "size of group = " << this->UC.size() << std::endl;
	for (auto a : this->UC) {
		std::cout << "i, j, n =" << a.X << "," << a.Y <<","<<a.Number << std::endl;
	}
	std::cout << "endofgroup" << std::endl;
}

bool Group::operator>(const Group &A) const{
	if (this->UC.size() > A.UC.size()) {
		return true;
	}
	return false;
}

bool Group::operator<(const Group &A) const {
	if (this->UC.size() < A.UC.size()) {
		return true;
	}
	return false;
}

bool Group::isContains(Group &A) {
	for (auto &a : A.UC) {
		auto it = std::find(this->UC.begin(), this->UC.end(), a);
		if (it == this->UC.end()) {
			return false;
		}
	}
	return true;
}

bool Group::isOverlap(Group &A) {
	std::vector<UnknownCells> tmp;
	std::set_intersection(this->UC.begin(), this->UC.end(), A.UC.begin(), A.UC.end(), std::back_inserter(tmp));
	return (!tmp.empty());
}

void Group::subtraction(Group &A) {
	for (auto &a : A.UC) {
		auto it = std::find(this->UC.begin(), this->UC.end(), a);
		this->UC.erase(it);
	}
	//auto it = std::search(this->UC.begin(), this->UC.end(), A.UC.begin(), A.UC.end());
	//this->UC.erase(it, it + A.UC.size());
	this->NofM -= A.NofM;
}

Group Group::getOverlap(Group &A) {
	Group tmp(this->Xc, this->Yc, this->NofM);
	tmp.UC = this->UC;
	std::vector<UnknownCells> temp;
	std::set_intersection(tmp.UC.begin(), tmp.UC.end(), A.UC.begin(), A.UC.end(), std::back_inserter(temp));
	tmp.UC = temp;
	tmp.NofM = NofM - (A.UC.size() - tmp.UC.size());
#ifdef DEBUG
	std::cout << "tmp.NofM = " << NofM << ", A.UC.size() = " << A.UC.size() << ", tmp.UC.size() = " << tmp.UC.size() << std::endl;
#endif // DEBUG
	return tmp;

}

