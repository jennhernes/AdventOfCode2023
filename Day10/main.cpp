#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct Pos
{
    int x{};
    int y{};

    Pos operator+(Pos other) const
    {
        return Pos{this->x + other.x, this->y + other.y};
    }
};

int main()
{
    std::ifstream file{"../test.txt"};
    std::string line;
    std::stringstream ss;

    std::vector<std::vector<char>> grid{};
    std::vector<Pos> ground{};
    std::vector<std::array<Pos, 2>> loop{};
    int x;
    int y{};
    int sx{};
    int sy{};
    while (std::getline(file, line))
    {
        x = 0;
        std::vector<char> row{};
        for (const auto c: line)
        {
            if (c == 'S')
            {
                sx = x;
                sy = y;
            } else if (c == '.')
            {
                ground.push_back({x, y});
            }
            row.push_back(c);
            ++x;
        }
        grid.push_back(row);
        ++y;
    }

    std::cout << grid.size() << " " << sx << " " << sy << '\n';
    Pos direction{0, 0};
    if (sx < grid.size() - 1 && (grid[sy][sx + 1] == '-' || grid[sy][sx + 1] == 'J' || grid[sy][sx + 1] == '7'))
    {
        direction.x = 1;
    } else if (sy < grid.size() - 1 && (grid[sy + 1][sx] == '|' || grid[sy + 1][sx] == 'L' || grid[sy + 1][sx] == 'J'))
    {
        direction.y = 1;
    } else if (sx > 0)
    {
        direction.x = -1;
    } else
    {
        direction.y = -1;
    }

    Pos currentPos{sx + direction.x, sy + direction.y};
    int length{1};
    while (grid[currentPos.y][currentPos.x] != 'S')
    {
        loop.push_back(std::array<Pos, 2>{Pos{currentPos.x, currentPos.y}, Pos{direction.x, direction.y}});
        switch (grid[currentPos.y][currentPos.x])
        {
            case 'L':
            case '7':
            {
                int tmp = direction.x;
                direction.x = direction.y;
                direction.y = tmp;
                break;
            }
            case 'J':
            case 'F':
            {
                int tmp = direction.x;
                direction.x = direction.y * -1;
                direction.y = tmp * -1;
                break;
            }
            default: break;
        }
        currentPos.x += direction.x;
        currentPos.y += direction.y;
        length++;
    }

    std::cout << length / 2 << '\n';
}
