#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <numeric>

int main() {
	std::string line;
	int ans = 0;

	std::ifstream calibrationDoc("calibration1.txt");

	if (calibrationDoc.is_open()) {
		while (std::getline(calibrationDoc, line)) {
			auto leftItr = line.begin();
			auto rightItr = line.end() - 1;
			int value;
			int firstDigit = -1;
			int lastDigit = -1;
			while (leftItr <= rightItr) {
				if (std::isdigit(*leftItr)) {
					if (firstDigit < 0) {
						char f = (*leftItr);
						firstDigit = std::atoi(&f);
					}
				}
				else {
					leftItr++;
				}

				if (std::isdigit(*rightItr)) {
					if (lastDigit < 0) {
						char l = (*rightItr);
						lastDigit = std::atoi(&l);
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