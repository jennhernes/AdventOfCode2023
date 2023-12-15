#include <fstream>
#include <iostream>
#include <vector>

struct Pos
{
    int x{};
    int y{};
};

int main()
{
    std::ifstream file {"../input.txt"};

    std::vector<Pos> galaxies {};
    std::vector<int> emptyRows {};
    std::vector<int> emptyCols {};
    std::string line;

    int x{};
    int y{};
    while(std::getline(file, line))
    {
        if (line.empty()) continue;
        if (emptyCols.empty())
        {
            for (int i {}; i < line.size(); ++i)
            {
                emptyCols.push_back(i);
            }
        }
        x = 0;
        bool empty {true};
        for (auto c : line)
        {
            if (c == '#')
            {
                galaxies.push_back({x,y});
                auto index{
                    std::find_if(emptyCols.begin(), emptyCols.end(),
                              [&](const auto i) { return i == x; }) - emptyCols.begin()};
                if (index < emptyCols.size()) emptyCols.erase(emptyCols.begin() + index);
                empty = false;
            }
            ++x;
        }
        if (empty) emptyRows.push_back(y);
        ++y;
    }

    for (auto r : emptyRows)
    {
        std::cout << r << " ";
    }
    std::cout << '\n';

    for (auto c : emptyCols)
    {
        std::cout << c << " ";
    }
    std::cout << '\n';

    // for (auto pos : galaxies)
    // {
    //     std::cout << "(" << pos.x << "," << pos.y << ")\n";
    // }

    long long sum {};
    for (int i {}; i < galaxies.size() - 1; ++i)
    {
        for (int j {i+1}; j < galaxies.size(); ++j)
        {
            for (auto r : emptyRows)
            {
                if ((r > galaxies[i].y && r < galaxies[j].y) || (r > galaxies[j].y && r < galaxies[i].y))
                {
                    sum += 999999;
                }
            }
            for (auto c : emptyCols)
            {
                if ((c > galaxies[i].x && c < galaxies[j].x) || (c > galaxies[j].x && c < galaxies[i].x))
                {
                    sum += 999999;
                }
            }
            sum += abs(galaxies[i].x - galaxies[j].x) + abs(galaxies[i].y - galaxies[j].y);
        }
    }

    std::cout << sum << '\n';
}
