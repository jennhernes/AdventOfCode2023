#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>


int main()
{
    std::ifstream file{"../input.txt"};
    std::string line;
    std::stringstream ss;

    std::vector<std::vector<char>> grid{};
    std::vector<char> row{};
    int x;
    int y{};
    int sx{};
    int sy{};
    while (std::getline(file, line))
    {
        if (sx == 0 && sy == 0)
        {
            x = 0;
            for (const auto c: line)
            {
                if (c == 'S')
                {
                    sx = x;
                    sy = y;
                    break;
                }
                ++x;
            }
            ++y;
        }
        grid.emplace_back(line.begin(), line.end());
    }

    std::array<int, 2> direction{0, 0};
    if (sx < grid.size() - 1 && (grid[sy][sx + 1] == '-' || grid[sy][sx + 1] == 'J' || grid[sy][sx + 1] == '7'))
    {
        direction[1] = 1;
    } else if (sy < grid.size() - 1 && (grid[sy + 1][sx] == '|' || grid[sy + 1][sx] == 'L' || grid[sy + 1][sx] == 'J'))
    {
        direction[0] = 1;
    } else
    {
        direction[1] = -1;
    }

    std::map<int, std::vector<int>> loop{};
    std::array<int, 2> currentPos{sy + direction[0], sx + direction[1]};
    int length{1};
    while (grid[currentPos[0]][currentPos[1]] != 'S')
    {
        if (!loop.contains(currentPos[0])) loop[currentPos[0]] = {};
        loop[currentPos[0]].push_back(currentPos[1]);
        switch (grid[currentPos[0]][currentPos[1]])
        {
            case 'L':
            case '7':
            {
                int tmp = direction[1];
                direction[1] = direction[0];
                direction[0] = tmp;
                break;
            }
            case 'J':
            case 'F':
            {
                int tmp = direction[1];
                direction[1] = direction[0] * -1;
                direction[0] = tmp * -1;
                break;
            }
            default: break;
        }
        currentPos[1] += direction[1];
        currentPos[0] += direction[0];
        length++;
    }

    std::cout << length / 2 << '\n';

    int previousCorner{};
    bool inRegion;
    int total{};
    for (int i{}; i < grid.size(); ++i)
    {
        inRegion = false;
        for (int j{}; j < grid[i].size(); ++j)
        {
            if (grid[i][j] == 'S' || (loop.contains(i) && std::find(loop.at(i).begin(), loop.at(i).end(), j) != loop.
                                      at(i).end()))
            {
                if (grid[i][j] == 'F' || grid[i][j] == '7') // || grid[i][j] == 'S')
                {
                    if (previousCorner == 1) previousCorner = 0;
                    else if (previousCorner == 0) previousCorner = 1;
                    else
                    {
                        inRegion = !inRegion;
                        previousCorner = 0;
                    }
                } else if (grid[i][j] == 'L' || grid[i][j] == 'J' || grid[i][j] == 'S')
                {
                    if (previousCorner == -1) previousCorner = 0;
                    else if (previousCorner == 0) previousCorner = -1;
                    else
                    {
                        inRegion = !inRegion;
                        previousCorner = 0;
                    }
                } else if (grid[i][j] == '|')
                {
                    inRegion = !inRegion;
                    previousCorner = 0;
                }
            } else if (inRegion)
            {
                ++total;
            }
        }
    }

    std::cout << total << '\n';
}
