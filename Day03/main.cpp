#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <array>
#include <sstream>

struct Gear
{
    int x{};
    int y{};
    std::array<int, 2> nums{-1, -1};
};

int main()
{
    std::vector<std::vector<char>> schematic{};
    std::ifstream file{"../input.txt"};
    std::string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        schematic.emplace_back(line.begin(), line.end());
    }

    int total{};
    std::vector<Gear> gears{};
    std::stringstream ss;
    for (int i{}; i < schematic.size(); ++i)
    {
        for (int j{}; j < schematic[i].size(); ++j)
        {
            if (isdigit(schematic[i][j]))
            {
                int n{schematic[i][j] - '0'};
                int left = j;
                while (j + 1 < schematic[i].size() && isdigit(schematic[i][j + 1]))
                {
                    n = n * 10 + (schematic[i][j + 1] - '0');
                    ++j;
                }
                int right = j;
                bool valid{false};
                for (int y{std::max(0, i - 1)};
                     y < std::min(static_cast<int>(schematic.size()), i + 2);
                     ++y)
                {
                    for (int x{std::max(0, left - 1)};
                         x < std::min(static_cast<int>(schematic[i].size()), right + 2);
                         ++x)
                    {
                        if (!valid && !isdigit(schematic[y][x]) && schematic[y][x] != '.')
                        {
                            total += n;
                            valid = true;
                        }

                        if (schematic[y][x] == '*')
                        {
                            auto is_gear = [&](const Gear& g) { return g.x == x && g.y == y; };
                            int gIndex{
                                static_cast<int>(std::find_if(gears.begin(), gears.end(), is_gear)
                                                 - gears.begin())
                            };
                            if (gIndex == gears.size())
                            {
                                gears.emplace_back(x, y);
                            }
                            if (gears[gIndex].nums[0] == -1)
                            {
                                gears[gIndex].nums[0] = n;
                            } else
                            {
                                gears[gIndex].nums[1] = n;
                            }
                        }
                    }
                }
            }
        }
    }

    int ratios{};
    for (auto g: gears)
    {
        if (g.nums[0] > -1 && g.nums[1] > -1)
        {
            ratios += g.nums[0] * g.nums[1];
        }
    }
    std::cout << total << " " << ratios << '\n';
}
