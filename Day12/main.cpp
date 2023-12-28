#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

struct Record
{
    std::string row{};
    std::vector<int> groups{};

    int getPossibleArrangementCount() const;
};

int Record::getPossibleArrangementCount() const
{
    // std::cout << "Processing " << row << " with groups ";
    for (auto n: groups)
    {
        // std::cout << n << " ";
    }
    // std::cout << '\n';
    std::vector<int> spaces{};
    for (int i{}; i < groups.size(); ++i)
    {
        spaces.push_back(1);
    }
    spaces[0] = 0;
    int result{};
    const int spacingMax{static_cast<int>(row.size()) - std::reduce(groups.begin(), groups.end())};
    while (std::reduce(spaces.begin(), spaces.end()) <= spacingMax)
    {
        // std::cout << "Current spacing test ";
        for (auto n: spaces)
        {
            // std::cout << n << " ";
        }
        // std::cout << '\n';
        int l{};
        bool ok{true};
        for (int i{}; ok && i < groups.size(); ++i)
        {
            if (l + spaces[i] > row.size())
            {
                ok = false;
                break;
            }
            // std::cout << "Spaces ";
            for (int j{}; j < spaces[i]; ++j)
            {
                // std::cout << j + l << "=" << row[j + l] << " ";
                if (row[j + l] == '#')
                {
                    ok = false;
                    break;
                }
            }
            l += spaces[i];
            // std::cout << "Group ";
            for (int j{}; j < groups[i]; ++j)
            {
                // std::cout << j + l << "=" << row[j + l] << " ";
                if (row[j + l] == '.')
                {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
            if (l + groups[i] < row.size() && row[l + groups[i]] == '#')
            {
                ok = false;
                break;
            }
            l += groups[i];
        }
        for (int i{l}; i < row.size(); ++i)
        {
            if (row[i] == '#')
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            // std::cout << "Above was ok!\n";
            ++result;
        }
        ++spaces[spaces.size() - 1];
        auto i{spaces.size() - 1};
        while (i > 0 && std::reduce(spaces.begin(), spaces.end()) > spacingMax)
        {
            spaces[i] = 1;
            ++spaces[i - 1];
            --i;
        }
    }
    // std::cout << '\n';
    std::cout << result << '\n';
    return result;
}

int main()
{
    std::ifstream file{"../test.txt"};
    std::string line;
    std::stringstream ss;

    int total{};
    while (std::getline(file, line))
    {
        ss.clear();
        ss << line;
        ss >> line;
        std::string row {line};
        for (int i{}; i < 4; ++i)
        {
            row = row.append("?").append(line);
        }
        Record record{row, {}};
        std::vector<int> initialGroups {};
        while (std::getline(ss, line, ','))
        {
            initialGroups.push_back(stoi(line));
        }
        for (int i{}; i < 4; ++i)
        {
            for (int j{}; j < initialGroups.size(); ++j)
            record.groups.push_back(initialGroups[j]);
        }
        std::cout << record.row << '\n';
        total += record.getPossibleArrangementCount();
        // break;
    }

    std::cout << total << '\n';
}
