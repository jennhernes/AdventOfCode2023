#include <fstream>
#include <iostream>
#include <map>
#include <vector>

int main()
{
    std::ifstream file{"../input.txt"};
    std::string line;
    std::vector<std::vector<char>> grid{};
    long long sum{};
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            if (grid.empty()) continue;
            for (auto c : grid[0])
            {
                std::cout << c;
            }
            std::cout << '\n';
            std::map<int, std::vector<int>> matchesRows{};
            std::map<int, std::vector<int>> matchesCols{};
            for (int i{}; i < grid.size(); ++i)
            {
                matchesRows[i] = {};
                for (int j{}; j < grid.size(); ++j)
                {
                    if (i == j) continue;
                    bool success{true};
                    for (int k{}; k < grid[0].size(); ++k)
                    {
                        if (grid[i][k] != grid[j][k])
                        {
                            success = false;
                            break;
                        }
                    }
                    if (success)
                    {
                        matchesRows[i].push_back(j);
                    }
                }
                // std::cout << i << " row matches: ";
                // for (auto n : matchesRows[i])
                // {
                //     std::cout << n << " ";
                // }
                // std::cout << '\n';
            }
            for (int i{}; i < grid[0].size(); ++i)
            {
                matchesCols[i] = {};
                for (int j{}; j < grid[0].size(); ++j)
                {
                    if (i == j) continue;
                    bool success{true};
                    for (int k{}; k < grid.size(); ++k)
                    {
                        if (grid[k][i] != grid[k][j])
                        {
                            success = false;
                            break;
                        }
                    }
                    if (success)
                    {
                        matchesCols[i].push_back(j);
                    }
                }
                // std::cout << i << " col matches: ";
                // for (auto n : matchesCols[i])
                // {
                //     std::cout << n << " ";
                // }
                // std::cout << '\n';
            }

            for (int i{1}; i < grid.size(); ++i)
            {
                bool success{true};
                for (int j{1}; j < grid.size(); ++j)
                {
                    // std::cout << j << ": " << i - j << ", " << i + j - 1 << " | ";
                    if (i - j < 0 || i + j - 1 > grid.size() - 1) break;
                    if (find(matchesRows[i - j].begin(), matchesRows[i - j].end(), i + j - 1)
                        == matchesRows[i - j].end())
                    {
                        success = false;
                        break;
                    }
                }

                if (success)
                {
                    // std::cout << "Found reflection line before " << i << '\n';
                    sum += i * 100;
                }
            }
            for (int i{1}; i < grid[0].size(); ++i)
            {
                bool success{true};
                for (int j{1}; j < grid[0].size(); ++j)
                {
                    if (i - j < 0 || i + j - 1 > grid[0].size() - 1) break;
                    if (find(matchesCols[i - j].begin(), matchesCols[i - j].end(), i + j - 1)
                        == matchesCols[i - j].end())
                    {
                        success = false;
                        break;
                    }
                }

                if (success)
                {
                    sum += i;
                }
            }
            std::cout << sum << '\n';
            grid.clear();
            continue;
        }

        std::vector<char> row{};
        for (auto c: line)
        {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    std::cout << sum << '\n';
}
