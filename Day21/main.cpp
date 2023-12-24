#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

struct Pos
{
    int x{};
    int y{};
};

int main()
{
    // std::ifstream file {"../test.txt"};
    // constexpr int steps {6};
    std::ifstream file {"../input.txt"};
    constexpr int steps {64};
    std::string line;
    std::vector<std::vector<char>> grid {};
    while (std::getline(file, line))
    {
        grid.emplace_back(line.begin(), line.end());
    }

    std::map<int, std::vector<Pos>> possibleSteps {};
    for (int i{}; i < grid.size(); ++i)
    {
        for (int j{}; j < grid[i].size(); ++j)
        {
            if (grid[i][j] == 'S')
            {
                possibleSteps[0] = {{j,i}};
                break;
            }
        }
        if (possibleSteps.contains(0)) break;
    }

    for (int i{}; i < steps; ++i)
    {
        possibleSteps[i+1] = {};
        for (const auto& p : possibleSteps[i])
        {
            if (p.x > 0 && grid[p.y][p.x-1] != '#'
                && std::ranges::find_if(possibleSteps[i+1], [&](const auto pos)
                {
                    return pos.x == p.x-1 && pos.y == p.y;
                }) == possibleSteps[i+1].end())
            {
                possibleSteps[i+1].push_back({p.x-1, p.y});
            }

            if (p.y > 0 && grid[p.y-1][p.x] != '#'
                && std::ranges::find_if(possibleSteps[i+1], [&](const auto pos)
                {
                    return pos.x == p.x && pos.y == p.y-1;
                }) == possibleSteps[i+1].end())
            {
                possibleSteps[i+1].push_back({p.x, p.y-1});
            }

            if (p.x < grid[p.y].size()-1 && grid[p.y][p.x+1] != '#'
                && std::ranges::find_if(possibleSteps[i+1], [&](const auto pos)
                {
                    return pos.x == p.x+1 && pos.y == p.y;
                }) == possibleSteps[i+1].end())
            {
                possibleSteps[i+1].push_back({p.x+1, p.y});
            }

            if (p.y < grid.size()-1 && grid[p.y+1][p.x] != '#'
                && std::ranges::find_if(possibleSteps[i+1], [&](const auto pos)
                {
                    return pos.x == p.x && pos.y == p.y+1;
                }) == possibleSteps[i+1].end())
            {
                possibleSteps[i+1].push_back({p.x, p.y+1});
            }
        }
    }

    // for (auto kvp : possibleSteps)
    // {
    //     std::cout << kvp.first << ": ";
    //     for (int i{}; i < kvp.second.size(); ++i)
    //     {
    //         std::cout << kvp.second[i].x << "," << kvp.second[i].y << " | ";
    //     }
    //     std::cout << '\n';
    // }
    std::cout << possibleSteps[steps].size() << '\n';
}
