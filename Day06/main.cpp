#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int numDigits(const long long n)
{
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    return 0;
}

int main()
{
    std::ifstream file{"../input.txt"};
    std::vector<int> times;
    std::string line;
    std::stringstream ss;

    std::getline(file, line);
    ss.clear();
    ss.str(line);
    ss >> line;
    int n;
    long long time{};
    while (ss >> n)
    {
        times.push_back(n);
        if (time != 0)
        {
            int num_digits{numDigits(n)};
            for (int i{}; i < num_digits; ++i)
            {
                time *= 10;
            }
        }
        time += n;
    }

    std::getline(file, line);
    ss.clear();
    ss.str(line);
    ss >> line;
    int total{1};
    int index{};
    int round;
    long long distance{};
    while (ss >> n)
    {
        round = 0;
        int mid{times[index] / 2};
        while (mid * (times[index] - mid) > n)
        {
            ++round;
            --mid;
        }
        round *= 2;
        if (times[index] % 2 == 0) --round;
        total *= round;
        ++index;

        if (distance != 0)
        {
            int num_digits{numDigits(n)};
            for (int i{}; i < num_digits; ++i)
            {
                distance *= 10;
            }
        }
        distance += n;
    }

    long long roundLong;
    long long midLong{time / 2};
    long long left {0};
    long long right {midLong};
    long long test {midLong / 2};
    while (left < right + 1)
    {
        // std::cout << mid << " ";
        if (test * (time-test) < distance)
        {
            left = test + 1;
        }
        else
        {
            right = test - 1;
        }
        test = left + (right - left) / 2;
    }
    roundLong = midLong - test;
    if (left != right) ++roundLong;
    roundLong *= 2;
    if (time % 2 == 0) --roundLong;

    std::cout << total << " | " << roundLong << '\n';
}
