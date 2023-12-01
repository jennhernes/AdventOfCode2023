#include <fstream>
#include <iostream>
#include <sstream>
#include<ranges>
#include <regex>


std::string replaceSpelledDigits(const std::string_view input)
{
    std::string result{input};
    result = std::regex_replace(result, std::regex("one"), "o1e");
    result = std::regex_replace(result, std::regex("two"), "t2o");
    result = std::regex_replace(result, std::regex("three"), "t3e");
    result = std::regex_replace(result, std::regex("four"), "4");
    result = std::regex_replace(result, std::regex("five"), "5e");
    result = std::regex_replace(result, std::regex("six"), "6");
    result = std::regex_replace(result, std::regex("seven"), "7n");
    result = std::regex_replace(result, std::regex("eight"), "e8t");
    result = std::regex_replace(result, std::regex("nine"), "n9e");
    return result;
}

void GetCalibrationSum(const bool isPart2)
{
    std::ifstream file{"../input.txt"};

    std::string line;
    int total{};
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        if (isPart2)
        {
            line = replaceSpelledDigits(line);
        }
        // std::cout << line << " ";
        std::stringstream ss{};
        for (auto c: line)
        {
            if (c >= '0' && c <= '9')
            {
                ss << c;
                // std::cout << c << " ";
                break;
            }
        }
        for (auto c: line | std::views::reverse)
        {
            if (c >= '0' && c <= '9')
            {
                ss << c;
                // std::cout << c << " ";
                break;
            }
        }
        int value{};
        ss >> value;
        // std::cout << value << '\n';
        total += value;
    }

    std::cout << total << std::endl;
}

int main(int, char**)
{
    GetCalibrationSum(true);
}
