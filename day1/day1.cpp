#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <numeric>
#include <unordered_map>

int main() {
	std::string line;
	int ans = 0;

	std::ifstream calibrationDoc("calibration.txt");

	std::unordered_map<std::string, int> lexMap{
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5},
		{"six", 6},
		{"seven", 7},
		{"eight", 8},
		{"nine", 9}
	};

	if (calibrationDoc.is_open()) {
		while (std::getline(calibrationDoc, line)) {
			int leftItr = 0;
			int rightItr = line.size() - 1;
			int value;
			int firstDigit = -1;
			int lastDigit = -1;
			while (leftItr <= line.size() && rightItr > 0) {
				if (firstDigit < 0) {
					if (std::isdigit(line[leftItr]))
					{
						char f = (line[leftItr]);
						firstDigit = std::atoi(&f);
					}
					else if ((leftItr + 2 < line.size()) && lexMap.find(line.substr(leftItr, 3)) != lexMap.end())
					{
						firstDigit = lexMap[line.substr(leftItr, 3)];
						leftItr = leftItr + 3;
					}
					else if ((leftItr + 3 < line.size()) && lexMap.find(line.substr(leftItr, 4)) != lexMap.end())
					{
						firstDigit = lexMap[line.substr(leftItr, 4)];
						leftItr = leftItr + 4;
					}
					else if ((leftItr + 4 < line.size()) && lexMap.find(line.substr(leftItr, 5)) != lexMap.end())
					{
						firstDigit = lexMap[line.substr(leftItr, 5)];
						leftItr = leftItr + 5;
					}
					else
					{
						leftItr++;
					}
				}
				else {
					leftItr++;
				}

				if (lastDigit < 0) {
					if (std::isdigit(line[rightItr]))
					{
						char f = (line[rightItr]);
						lastDigit = std::atoi(&f);
					}
					else if ((rightItr - 2 > 0) && lexMap.find(line.substr(rightItr - 2, 3)) != lexMap.end())
					{
						lastDigit = lexMap[line.substr(rightItr - 2, 3)];
						rightItr = rightItr - 3;
					}
					else if ((rightItr - 3 > 0) && lexMap.find(line.substr(rightItr - 3, 4)) != lexMap.end())
					{
						lastDigit = lexMap[line.substr(rightItr - 3, 4)];
						rightItr = rightItr - 4;
					}
					else if ((rightItr - 4 > 0) && lexMap.find(line.substr(rightItr - 4, 5)) != lexMap.end())
					{
						lastDigit = lexMap[line.substr(rightItr - 4, 5)];
						rightItr = rightItr - 5;
					}
					else
					{
						rightItr--;
					}
				}
				else {
					rightItr--;
				}

				if (firstDigit > 0 && lastDigit > 0) {
					break;
				}
			}
			if (firstDigit < 0) {
				value = (lastDigit * 10) + lastDigit;
			}
			else if (lastDigit < 0) {
				value = (firstDigit * 10) + firstDigit;
			}
			else {
				value = (firstDigit * 10) + lastDigit;
			}
			//result.push_back(value);
			ans += value;
		}

		calibrationDoc.close();

		std::cout << ans << std::endl;

		return ans;
	}
	else {
		std::cout << "Unable to open file." << std::endl;
		return -1;
	}
}