#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <numeric>
#include <unordered_map>

int main() {

	std::string line;

	
	long powerSum = 0;

	std::ifstream gameLog("game.txt");

	if (gameLog.is_open()) {
		while (std::getline(gameLog, line)) {

			std::unordered_map<std::string, int> minReqCubes{
				{"red", 0},
				{"green", 0},
				{"blue", 0}
			};

			long power = 1;

			std::string gameInfo = line.substr(line.find(" "));

			for (auto itr = gameInfo.begin(); itr != gameInfo.end() - 1; itr++) {
				if (*itr == ' ') {
					if (*(itr + 1) == 'r') {
						auto numItr = itr - 2;
						if (!std::isdigit(*numItr)) {
							numItr++;
						}
						int num = std::atoi(&(*numItr));
						if (minReqCubes["red"] < num) {
							minReqCubes["red"] = num;
						}
					}

					if (*(itr + 1) == 'g') {
						auto numItr = itr - 2;
						if (!std::isdigit(*numItr)) {
							numItr++;
						}
						int num = std::atoi(&(*numItr));
						if (minReqCubes["green"] < num) {
							minReqCubes["green"] = num;
						}
					}

					if (*(itr + 1) == 'b') {
						auto numItr = itr - 2;
						if (!std::isdigit(*numItr)) {
							numItr++;
						}
						int num = std::atoi(&(*numItr));
						if (minReqCubes["blue"] < num) {
							minReqCubes["blue"] = num;
						}
					}

				}
				else {
					continue;
				}
			}

			/*
			if (minReqCubes["red"] != 0) {
				power = power * minReqCubes["red"];
			}
			if (minReqCubes["green"] != 0) {
				power = power * minReqCubes["green"];
			}
			if (minReqCubes["blue"] != 0) {
				power = power * minReqCubes["blue"];
			}
			*/

			power = minReqCubes["red"] * minReqCubes["green"] * minReqCubes["blue"];
			powerSum += power;

		}
		std::cout << powerSum << std::endl;
		gameLog.close();
		return powerSum;
	}
	else {
		std::cout << "Unable to open file." << std::endl;
		return -1;
	}
	
}