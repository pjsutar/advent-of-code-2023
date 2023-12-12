#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>



int main() {
	std::string line;
	int pointsSum = 0;
	int count = 0;

	std::ifstream cards("cards.txt");

	if (cards.is_open()) {
		while (std::getline(cards, line)) {
			int points = 0;
			std::unordered_set<std::string> winNumsSet = {};
			std::vector<std::string> scratchedNums;

			std::string winNums = line.substr(line.find(":"), (line.find("|") - line.find(":")));
			std::string nums = line.substr(line.find("|"));

			std::stringstream swn(winNums);
			std::string winNum;
			while (swn >> winNum) {
				winNumsSet.insert(winNum);
			}

			std::stringstream syn(nums);
			std::string num;
			while (syn >> num) {
				scratchedNums.push_back(num);
			}

			for (auto num : scratchedNums) {
				if (winNumsSet.find(num) != winNumsSet.end()) {
					if (points == 0) {
						points++;
					}
					else {
						points = (points * 2);
					}
				}
			}
			pointsSum += points;

		}

		cards.close();

		std::cout << pointsSum << std::endl;
		return pointsSum;
	}
	else {
		std::cout << "Unable to open file." << std::endl;
		return -1;
	}
}
