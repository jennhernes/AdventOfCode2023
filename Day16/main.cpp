#include <array>
#include <fstream>
#include <iostream>
#include <vector>

constexpr int NORTH{1};
constexpr int SOUTH{2};
constexpr int WEST{4};
constexpr int EAST{8};

int getEnergizedCellCount(const std::vector<std::vector<char>>& grid, std::array<int, 3> start)
{
    std::vector<std::vector<int>> checkedDirections{}; //1 2 4 8 <- N S W E
    for (const auto& v: grid)
    {
        std::vector<int> row{};
        for (auto c: v)
        {
            row.push_back(0);
        }
        checkedDirections.push_back(row);
    }

    std::vector<std::array<int, 3>> currentPos{start};
    while (!currentPos.empty())
    {
        std::array<int, 2> nextPos{};
        int nextDirection{currentPos[0][2]};
        if (nextDirection == NORTH)
        {
            nextPos[0] = currentPos[0][0] - 1;
            nextPos[1] = currentPos[0][1];
        } else if (nextDirection == SOUTH)
        {
            nextPos[0] = currentPos[0][0] + 1;
            nextPos[1] = currentPos[0][1];
        } else if (nextDirection == WEST)
        {
            nextPos[0] = currentPos[0][0];
            nextPos[1] = currentPos[0][1] - 1;
        } else
        {
            nextPos[0] = currentPos[0][0];
            nextPos[1] = currentPos[0][1] + 1;
        }
        currentPos.erase(currentPos.begin());

        if ((nextPos[0] < 0 || nextPos[0] >= grid.size())
            || (nextPos[1] < 0 || nextPos[1] >= grid[0].size())
            || (checkedDirections[nextPos[0]][nextPos[1]] & nextDirection))
        {
            continue;
        }

        checkedDirections[nextPos[0]][nextPos[1]] += nextDirection;
        if (grid[nextPos[0]][nextPos[1]] == '.')
        {
            currentPos.push_back({nextPos[0], nextPos[1], nextDirection});
        } else if (grid[nextPos[0]][nextPos[1]] == '/')
        {
            if (nextDirection == NORTH) nextDirection = EAST;
            else if (nextDirection == SOUTH) nextDirection = WEST;
            else if (nextDirection == WEST) nextDirection = SOUTH;
            else nextDirection = NORTH;
            currentPos.push_back({nextPos[0], nextPos[1], nextDirection});
        } else if (grid[nextPos[0]][nextPos[1]] == '\\')
        {
            if (nextDirection == NORTH) nextDirection = WEST;
            else if (nextDirection == SOUTH) nextDirection = EAST;
            else if (nextDirection == WEST) nextDirection = NORTH;
            else nextDirection = SOUTH;
            currentPos.push_back({nextPos[0], nextPos[1], nextDirection});
        } else if (grid[nextPos[0]][nextPos[1]] == '|')
        {
            if (nextDirection == NORTH || nextDirection == SOUTH)
            {
                currentPos.push_back({nextPos[0], nextPos[1], nextDirection});
            } else
            {
                currentPos.push_back({nextPos[0], nextPos[1], NORTH});
                currentPos.push_back({nextPos[0], nextPos[1], SOUTH});
            }
        } else if (grid[nextPos[0]][nextPos[1]] == '-')
        {
            if (nextDirection == WEST || nextDirection == EAST)
            {
                currentPos.push_back({nextPos[0], nextPos[1], nextDirection});
            } else
            {
                currentPos.push_back({nextPos[0], nextPos[1], WEST});
                currentPos.push_back({nextPos[0], nextPos[1], EAST});
            }
        }
    }

    int total{};
    for (const auto& v: checkedDirections)
    {
        for (auto n: v)
        {
            if (n > 0) total++;
        }
    }
    return total;
}

int main()
{
    std::ifstream file{"../input.txt"};
    std::string line;
    std::vector<std::vector<char>> grid{};

    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        grid.emplace_back(line.begin(), line.end());
    }

    int max{};
    for (int i{}; i < grid.size(); ++i)
    {
        max = std::max(max, getEnergizedCellCount(grid, {i,-1, EAST}));
        max = std::max(max, getEnergizedCellCount(grid, {i,static_cast<int>(grid.size()), WEST}));
    }
    for (int i{}; i < grid[0].size(); ++i)
    {
        max = std::max(max, getEnergizedCellCount(grid, {-1, i, SOUTH}));
        max = std::max(max, getEnergizedCellCount(grid, {static_cast<int>(grid[0].size()), i, NORTH}));
    }
    std::cout << max << '\n';
}
