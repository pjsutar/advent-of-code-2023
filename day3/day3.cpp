#include <iostream>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

int main() {
	std::vector<std::string> grid;

	std::unordered_map<int, std::vector<int>> engineParts;

	std::ifstream engineDoc("engine.txt");

	std::string line;

	long partSum = 0;

	long gearRatioSum = 0;

	if (engineDoc.is_open()) {
		while (std::getline(engineDoc, line)) {
			grid.push_back(line);
		}
		engineDoc.close();
	}
	else {
		std::cout << "Unable to open file." << std::endl;
	}

	for (int row = 1; row < grid.size() - 1; row++) {
		for (int col = 1; col < grid[0].size() - 1; col++) {

			std::vector<int> gearRatios;

			if (!std::isdigit(grid[row][col]) && grid[row][col] != '.') {
				// right side
				if (std::isdigit(grid[row][col + 1])) {
					auto itr = (grid[row].begin() + (col + 1));
					int part = std::atoi(&(*itr));
					engineParts[row].push_back(part);

					// Check for gear ratio
					if (grid[row][col] == '*') {
						gearRatios.push_back(part);
					}
				}

				// left side
				if (std::isdigit(grid[row][col - 1])) {
					int newCol = col - 1;
					while (newCol > 0 && std::isdigit(grid[row][newCol - 1])) {
						newCol--;
					}
					auto itr = (grid[row].begin() + newCol);
					int part = std::atoi(&(*itr));
					engineParts[row].push_back(part);

					// Check for gear ratio
					if (grid[row][col] == '*') {
						gearRatios.push_back(part);
					}
				}

				// top left side
				if (std::isdigit(grid[row - 1][col - 1])) {
					int newCol = col - 1;
					while (newCol > 0 && std::isdigit(grid[row - 1][newCol - 1])) {
						newCol--;
					}
					auto itr = (grid[row - 1].begin() + newCol);
					int part = std::atoi(&(*itr));
					engineParts[row - 1].push_back(part);

					// Check for gear ratio
					if (grid[row][col] == '*') {
						gearRatios.push_back(part);
					}
				}

				// bottom left side
				if (std::isdigit(grid[row + 1][col - 1])) {
					int newCol = col - 1;
					while (newCol > 0 && std::isdigit(grid[row + 1][newCol - 1])) {
						newCol--;
					}
					auto itr = (grid[row + 1].begin() + newCol);
					int part = std::atoi(&(*itr));
					engineParts[row + 1].push_back(part);

					// Check for gear ratio
					if (grid[row][col] == '*') {
						gearRatios.push_back(part);
					}
				}

				// top side
				if (!std::isdigit(grid[row - 1][col - 1]) && std::isdigit(grid[row - 1][col])) {
					auto itr = (grid[row - 1].begin() + col);
					int part = std::atoi(&(*itr));
					engineParts[row - 1].push_back(part);

					// Check for gear ratio
					if (grid[row][col] == '*') {
						gearRatios.push_back(part);
					}
				}

				// top right side
				if (!std::isdigit(grid[row - 1][col]) && std::isdigit(grid[row - 1][col + 1])) {
					auto itr = (grid[row - 1].begin() + (col + 1));
					int part = std::atoi(&(*itr));
					engineParts[row - 1].push_back(part);

					// Check for gear ratio
					if (grid[row][col] == '*') {
						gearRatios.push_back(part);
					}
				}

				// bottom side
				if (!std::isdigit(grid[row + 1][col - 1]) && std::isdigit(grid[row + 1][col])) {
					auto itr = (grid[row + 1].begin() + col);
					int part = std::atoi(&(*itr));
					engineParts[row + 1].push_back(part);

					// Check for gear ratio
					if (grid[row][col] == '*') {
						gearRatios.push_back(part);
					}
				}

				// bottom right side
				if (!std::isdigit(grid[row + 1][col]) && std::isdigit(grid[row + 1][col + 1])) {
					auto itr = (grid[row + 1].begin() + (col + 1));
					int part = std::atoi(&(*itr));
					engineParts[row + 1].push_back(part);

					// Check for gear ratio
					if (grid[row][col] == '*') {
						gearRatios.push_back(part);
					}
				}

				if (gearRatios.size() == 2) {
					gearRatioSum += gearRatios[0] * gearRatios[1];
				}
			}
			else {
				continue;
			}
		}
	}

	for (auto kvPair : engineParts) {
		partSum += std::accumulate(begin(kvPair.second), end(kvPair.second), 0);
	}

	//std::cout << partSum << std::endl;

	//return partSum;

	std::cout << gearRatioSum << std::endl;

	return gearRatioSum;

}