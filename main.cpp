#include "MineSweeper.h"
#include <chrono>

int main() {
	int x, y, n;
	std::cin >> x >> y;
	std::cout << std::endl;
	std::cin >> n;
	std::cout<<std::endl;
	MineSweeper MS(x, y, n);
	MS.SetConfig();
	auto start = std::chrono::system_clock::now();
	MS.FindNextCoords();
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << "s";

	std::cout << "THE END" << std::endl;
	system("pause");
	return 0;
}