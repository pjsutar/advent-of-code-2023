// day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cctype>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include <functional>
#include <map>
#include <ranges>

// Declarations

struct MapEntry
{
	int64_t destination = 0;
	int64_t source = 0;
	int64_t length = 0;
};

struct Map
{
	std::vector<MapEntry> entries;
};

template<typename T>
std::vector<T> SplitStringAndTransform(
	std::string_view input, std::string_view delimiter, std::function<T(std::string_view)> transform)
{
	return std::views::split(input, delimiter)
		| std::views::transform([&transform](const auto& subrange) { return transform(std::string_view{ subrange.begin(), subrange.end() }); })
		| std::ranges::to<std::vector>();
}

std::vector<int64_t> SplitSpaceSeparatedInt64s(std::string_view input);

std::vector<std::string> ReadAllLinesInFile(const std::filesystem::path& path);

std::pair<std::vector<int64_t>, std::vector<Map>> ReadInput(const std::filesystem::path& inputFile);

void PrintSolution(const std::filesystem::path& inputFile, bool /*shouldRender*/);

// Definitions
std::vector<int64_t> SplitSpaceSeparatedInt64s(std::string_view input)
{
	return SplitStringAndTransform<int64_t>(
		input, " ", [](std::string_view token) { return std::stoll(std::string{ token }); });
}

std::vector<std::string> ReadAllLinesInFile(const std::filesystem::path& path) {
    auto lines = std::vector<std::string>{};
    if (!std::filesystem::exists(path)) {
        return lines;
    }

    auto filestream = std::ifstream{ path };
    auto currentLine = std::string{};
    while (std::getline(filestream, currentLine)) {
        lines.emplace_back(currentLine);
    }
    return lines;
}

std::pair<std::vector<int64_t>, std::vector<Map>> ReadInput(const std::filesystem::path& inputFile)
{
	std::vector<std::string> input = ReadAllLinesInFile(inputFile);

	// Read seeds from the first line.
	std::vector<int64_t> seeds = SplitSpaceSeparatedInt64s(input[0].substr(input[0].find(':') + 2));

	// Seven maps in the input
	std::vector<Map> maps;
	maps.resize(7);
	int iMap = 0;

	// Read remaining lines into maps
	for (int i = 2; i < input.size(); ++i)
	{
		const std::string& line = input[i];

		// New lines mean we're starting the next map.
		if (line.empty())
		{
			++iMap;
			continue;
		}

		// Ignore labels.
		if (!std::isdigit(line[0]))
		{
			continue;
		}

		// Read all the ints on the line.
		std::vector<int64_t> tokens = SplitSpaceSeparatedInt64s(line);
		maps[iMap].entries.emplace_back(tokens[0], tokens[1], tokens[2]);
	}

	return std::make_pair(seeds, maps);
}

void PrintSolution(const std::filesystem::path& inputFile, bool /*shouldRender*/)
{
	auto [seeds, maps] = ReadInput(inputFile);
	int64_t minLocation = std::numeric_limits<int64_t>::max();
	for (int64_t location : seeds)
	{
		// Proceed through each map, remapping the value to the new frame of reference
		for (const Map& map : maps)
		{
			for (const MapEntry& entry : map.entries)
			{
				// If no entry matches, the value is unchanged.
				if (entry.source <= location && location < entry.source + entry.length)
				{
					location = entry.destination + (location - entry.source);
					break;
				}
			}
		}

		minLocation = std::min(minLocation, location);
	}

	std::cout << minLocation;
}

int main()
{
	bool shouldRender = false;
	PrintSolution("almanac.txt", shouldRender);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
