#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <numeric>
#include <vector>
#include <string>

struct raceInfo {
	std::vector<int> time;
	std::vector<int> distance;
};

raceInfo readInput(raceInfo& raceInfo, std::string inputfile);

raceInfo readInput(raceInfo& raceInfo, std::string inputfile) {
	std::string line;
	std::ifstream races(inputfile);

	if (races.is_open()) {
		while (std::getline(races, line)) {
			std::string lineVal = line.substr(line.find(":"));
			//std::stringstream ssline(lineVal);
			//std::string temp;
			auto itr = lineVal.begin();
			if (line[0] == 'T') {
				while ( itr < lineVal.end()) {
					if (std::isdigit(*itr) && itr != lineVal.end() - 1) {
						raceInfo.time.push_back(std::atoi(&(*itr)));
						while (isdigit(*itr) && itr < lineVal.end() - 1) {
							itr++;
						}
					}
					itr++;
				}
			}
			else if (line[0] == 'D') {
				while (itr < lineVal.end()) {
					if (std::isdigit(*itr) && itr != lineVal.end() - 1) {
						raceInfo.distance.push_back(std::atoi(&(*itr)));
						while (isdigit(*itr) && itr < lineVal.end() - 1) {
							itr++;
						}
					}
					itr++;
				}
			}
		}
		races.close();
	}
	else {
		std::cout << "Unable to open input file.";
		return raceInfo;
	}
	
	return raceInfo;
}

long findWays(int ways, const raceInfo& raceInfo);

long long findWays(const raceInfo& raceInfo) {
	long long ways = 1;
	for (int i = 0; i < raceInfo.time.size(); i++) {
		int time = raceInfo.time[i];
		int dist = raceInfo.distance[i];
		for (int j = 1; j < time; j++) {
			if ((j * (time - j)) > dist) {
				ways = ways * ((time - (2 * j)) + 1);
				break;
			}
		}
	}
	std::cout << ways << std::endl;
	return ways;
}

int main() {
	raceInfo raceData;
	readInput(raceData, "races.txt");
	long ans = findWays(raceData);
	return ans;
}

