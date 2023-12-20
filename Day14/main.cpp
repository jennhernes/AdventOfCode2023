#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    std::ifstream file{"../test.txt"};
    std::string line;
    std::vector<std::vector<char>> grid{};

    while (std::getline(file, line))
    {
        grid.emplace_back(line.begin(), line.end());
    }

    std::vector<int> loads{0};
    constexpr int rollCycles{1000000000};
    // constexpr int rollCycles{1};
    for (int a{}; a < rollCycles; ++a)
    {
        int load{};
        for (int i{}; i < grid.size(); ++i)
        {
            for (int j{}; j < grid[0].size(); ++j)
            {
                if (grid[i][j] == 'O')
                {
                    int k{1};
                    while (i - k >= 0 && grid[i - k][j] == '.')
                    {
                        grid[i - k][j] = 'O';
                        grid[i - k + 1][j] = '.';
                        ++k;
                    }
                }
            }
        }
        for (int i{}; i < grid.size(); ++i)
        {
            for (int j{}; j < grid[0].size(); ++j)
            {
                if (grid[i][j] == 'O')
                {
                    int k{1};
                    while (j - k >= 0 && grid[i][j - k] == '.')
                    {
                        grid[i][j - k] = 'O';
                        grid[i][j - k + 1] = '.';
                        ++k;
                    }
                }
            }
        }
        for (int i{static_cast<int>(grid.size() - 1)}; i >= 0; --i)
        {
            for (int j{static_cast<int>(grid[0].size() - 1)}; j >= 0; --j)
            {
                if (grid[i][j] == 'O')
                {
                    int k{1};
                    while (i + k < grid.size() && grid[i + k][j] == '.')
                    {
                        grid[i + k][j] = 'O';
                        grid[i + k - 1][j] = '.';
                        ++k;
                    }
                }
            }
        }
        for (int i{static_cast<int>(grid.size() - 1)}; i >= 0; --i)
        {
            for (int j{static_cast<int>(grid[0].size() - 1)}; j >= 0; --j)
            {
                if (grid[i][j] == 'O')
                {
                    int k{1};
                    while (j + k < grid.size() && grid[i][j + k] == '.')
                    {
                        grid[i][j + k] = 'O';
                        grid[i][j + k - 1] = '.';
                        ++k;
                    }
                    load += grid.size() - i - 1;
                }
            }
        }
        // const int cycleStart{static_cast<int>(std::find(loads.begin(), loads.end(), load) - loads.begin())};
        // if (cycleStart < loads.size())
        // {
        //     int mod = (rollCycles - a) % (static_cast<int>(loads.size()) - cycleStart + 1);
        //     for (auto l : loads)
        //     {
        //         std::cout << l << " ";
        //     }
        //     std::cout << '\n';
        //     std::cout << loads[cycleStart + mod] << '\n';
        //     break;
        // }
        // loads.push_back(load);
        loads[0] = load;
    }
    std::cout << loads[0] << '\n';
}
