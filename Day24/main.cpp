#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct Hailstone
{
    long long x{};
    long long y{};
    long long z{};
    long long vx{};
    long long vy{};
    long long vz{};
    long double slope{};
    long double intercept{};
};

int main()
{
    std::ifstream file{"../input.txt"};
    std::string line;
    std::stringstream ss;

    long long x{};
    long long y{};
    long long z{};
    long long vx{};
    long long vy{};
    long long vz{};
    char c{};
    long double slope;
    long double intercept;

    std::vector<Hailstone> hailstones{};
    while (std::getline(file, line))
    {
        ss.clear();
        ss << line;
        ss >> x;
        ss >> c;
        ss >> y;
        ss >> c;
        ss >> z;
        ss >> c;
        ss >> vx;
        ss >> c;
        ss >> vy;
        ss >> c;
        ss >> vz;
        slope = static_cast<double>(vy) / static_cast<double>(vx);
        intercept = static_cast<double>(y) - (slope * static_cast<double>(x));
        hailstones.push_back({x, y, z, vx, vy, vz, slope, intercept});
    }

    int total{};
    // long long lowerBound{7};
    // long long upperBound{27};
    long long lowerBound{200000000000000};
    long long upperBound{400000000000000};
    for (int i{}; i < hailstones.size()-1; ++i)
    {
        for (int j{i+1}; j < hailstones.size(); ++j)
        {
            if (std::abs(hailstones[i].slope - hailstones[j].slope) < 0.001) continue;

            long double xIntersect = (hailstones[i].intercept - hailstones[j].intercept)
                                    / (hailstones[j].slope - hailstones[i].slope);
            // std:: cout << "x=(" << hailstones[i].intercept << " - " << hailstones[j].intercept << ") / (" << hailstones[j].slope << " - " << hailstones[i].slope << ") = " << xIntersect << '\n';
            if ((hailstones[i].vx > 0 && xIntersect < hailstones[i].x) || (hailstones[i].vx < 0 && xIntersect > hailstones[i].x)
                || (hailstones[j].vx > 0 && xIntersect < hailstones[j].x) || (hailstones[j].vx < 0 && xIntersect > hailstones[j].x))
            {
                continue;
            }
            long double yIntersect = hailstones[i].slope * xIntersect + hailstones[i].intercept;
            if ((hailstones[i].vy > 0 && yIntersect < hailstones[i].y) || (hailstones[i].vy < 0 && yIntersect > hailstones[i].y)
                || (hailstones[j].vy > 0 && yIntersect < hailstones[j].y) || (hailstones[j].vy < 0 && yIntersect > hailstones[j].y))
            {
                continue;
            }
            if (xIntersect < lowerBound || xIntersect > upperBound
                || yIntersect < lowerBound || yIntersect > upperBound)
            {
                continue;
            }
            ++total;
            // std::cout << "Hailstone A: " << hailstones[i].x << ", " << hailstones[i].y << ", " << hailstones[i].z << " @ " << hailstones[i].vx << ", " << hailstones[i].vy << ", " << hailstones[i].vz << '\n';
            // std::cout << "Hailstone A: " << hailstones[j].x << ", " << hailstones[j].y << ", " << hailstones[j].z << " @ " << hailstones[j].vx << ", " << hailstones[j].vy << ", " << hailstones[j].vz << '\n';
            // std::cout << "Hailstones' paths cross at x=" << xIntersect << ", y=" << yIntersect << "\n\n";
        }
    }
    std::cout << total << '\n';
}
