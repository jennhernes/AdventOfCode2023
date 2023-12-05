#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <unordered_map>
#include <vector>

void PartOne()
{
    std::ifstream file{"../input.txt"};
    std::string line;
    std::stringstream ss;
    std::vector<unsigned long long> seeds{};

    std::getline(file, line);
    ss << line;
    ss >> line;
    unsigned long long n;
    while (ss >> n)
    {
        seeds.push_back(n);
    }

    std::getline(file, line);
    std::unordered_map<unsigned long long, std::array<unsigned long long, 2>> currentMap{};
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            for (auto& s: seeds)
            {
                for (auto [k,v]: currentMap)
                {
                    if (s >= k && s <= k + v[0])
                    {
                        s = (v[1] + s) - k;
                        break;
                    }
                }
            }

            for (auto s: seeds)
            {
                std::cout << s << " ";
            }
            std::cout << '\n';
            continue;
        }
        if (line.find("map") != std::string::npos)
        {
            std::cout << "map: " << line << '\n';
            currentMap.clear();
            continue;
        }

        ss.clear();
        ss.str(line);
        unsigned long long start{};
        unsigned long long end{};
        unsigned long long len{};
        ss >> end;
        ss >> start;
        ss >> len;
        currentMap[start] = std::array{len, end};
    }

    unsigned long long min{std::numeric_limits<unsigned long long>::max()};
    for (auto i: seeds)
    {
        min = std::min(min, i);
    }

    std::cout << min << '\n';
}

int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::ifstream file{"../input.txt"};
    std::string line;
    std::stringstream ss;
    std::map<unsigned long long, unsigned long long> seeds{};

    std::getline(file, line);
    ss << line;
    ss >> line;
    unsigned long long n;
    unsigned long long r;
    while (ss >> n)
    {
        ss >> r;
        seeds[n] = r;
    }

    // for (auto [s,r] : seeds)
    // {
    //     std::cout << s  << ": " << r << " | ";
    // }
    // std::cout << '\n';

    std::getline(file, line);
    std::map<unsigned long long, std::array<unsigned long long, 2>> currentMap{};
    std::map<unsigned long long, unsigned long long> prev{};
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            prev.clear();
            for (auto [k,v] : seeds)
            {
                prev[k] = v;
            }
            for (auto [k,v]: currentMap)
            {
                for (auto [s, r]: prev)
                {
                    if (s < k + v[0] && k < s + r)
                    {
                        if (k > s)
                        {
                            auto newS {k};
                            auto newR {s+r-k};
                            prev[s] = newS - s - 1;
                            seeds[s] = newS - s - 1;
                            seeds[v[1]] = newR;
                            continue;
                        }
                        if (s + r > k + v[0])
                        {
                            auto newS { k+v[0]};
                            auto newR {(s+r)-newS};
                            prev[s] = newS - s - 1;
                            seeds[s] = newS - s - 1;
                            prev[newS] = newR;
                        }
                        else
                        {
                            seeds[(v[1] + s) - k] = r;
                            seeds.erase(s);
                        }
                    }
                }
            }

            // for (auto [k,v] : currentMap)
            // {
            //     std::cout << k << ": " << v[0] << ", " << v[1] << " | ";
            // }
            // std::cout << '\n';
            //
            // for (auto [s,r] : seeds)
            // {
            //     std::cout << s  << ": " << r << " | ";
            // }
            // std::cout << '\n';
            continue;
        }
        if (line.find("map") != std::string::npos)
        {
            std::cout << "map: " << line << '\n';
            currentMap.clear();
            continue;
        }

        ss.clear();
        ss.str(line);
        unsigned long long start{};
        unsigned long long end{};
        unsigned long long len{};
        ss >> end;
        ss >> start;
        ss >> len;
        currentMap[start] = std::array{len, end};
    }

    unsigned long long min{std::numeric_limits<unsigned long long>::max()};
    for (auto [k,v]: seeds)
    {
        min = std::min(min, k);
    }

    std::cout << min << '\n';
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << "[ms]" << '\n';
}
