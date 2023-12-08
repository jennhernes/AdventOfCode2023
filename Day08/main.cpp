#include <fstream>
#include <iostream>
#include <sstream>

long long gcd(long long a, long long b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long lcm(std::vector<int> v)
{
    long long result {v[0]};
    for (int i {}; i < v.size(); ++i)
    {
        result = (static_cast<long long>(v[i]) * result) / (gcd(v[i], result));
    }
    return result;
}

int main()
{
    std::ifstream file{"../input.txt"};

    std::string directions;
    std::getline(file, directions);
    int steps;

    std::unordered_map<std::string, std::array<std::string, 2>> network{};
    std::string line;
    std::stringstream ss;
    std::string name;
    std::string left;
    std::string right;
    std::vector<std::string> currentLocations{};
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        ss.clear();
        ss << line;
        ss >> name;
        ss >> line; // =
        ss >> left;
        ss >> right;
        left = left.substr(1, left.size() - 2);
        right = right.substr(0, right.size() - 1);
        network[name] = std::array<std::string, 2>{left, right};
        if (name.find('A') != std::string::npos) currentLocations.push_back(name);
    }

    int i;
    std::vector<int> pathLengths;
    for (auto& s: currentLocations)
    {
        steps = 0;
        while (s.find('Z') == std::string::npos)
        {
            i = steps % static_cast<int>(directions.size());
            if (directions[i] == 'L')
            {
                s = network[s][0];
            } else
            {
                s = network[s][1];
            }
            ++steps;
        }
        pathLengths.push_back(steps);
    }

    std::cout << lcm(pathLengths) << '\n';
}
