#include <array>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

const int RED{0};
const int GREEN{1};
const int BLUE{2};

int main()
{
    std::ifstream file{"../input.txt"};
    std::string line{};
    std::stringstream ss;
    int sum{};
    int product{};
    int id{};
    std::array<int, 3> maxCubes{};
    int count{};
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        ss.clear();
        ss << line;

        ss >> line; // skip "Game"
        ss >> line;
        id = stoi(line.substr(0, line.size() - 1));
        count = 0;
        maxCubes[RED] = 0;
        maxCubes[GREEN] = 0;
        maxCubes[BLUE] = 0;
        while (ss >> count)
        {
            ss >> line;
            if (line.starts_with("red"))
            {
                maxCubes[RED] = std::max(maxCubes[RED], count);
            } else if (line.starts_with("blue"))
            {
                maxCubes[BLUE] = std::max(maxCubes[BLUE], count);
            } else if (line.starts_with("green"))
            {
                maxCubes[GREEN] = std::max(maxCubes[GREEN], count);
            }
        }
        if (maxCubes[RED] <= 12 && maxCubes[GREEN] <= 13 && maxCubes[BLUE] <= 14)
        {
            sum += id;
        }
        product += maxCubes[GREEN] * maxCubes[RED] * maxCubes[BLUE];
    }

    std::cout << sum << " " << product << '\n';
}
