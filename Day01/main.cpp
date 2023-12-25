#include <fstream>
#include <iostream>
#include <sstream>
#include<ranges>
#include <regex>


struct PosDigit
{
    std::size_t pos{};
    char digit{};
};

PosDigit findFirstWordDigit(const std::string& line)
{
    if (line.empty()) return {std::string::npos, -1};

    const std::array<std::string, 9> words{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    constexpr std::array<char, 9> digits{'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (std::size_t i{}; i < line.size(); ++i)
    {
        for (std::size_t j{}; j < words.size(); ++j)
        {
            if (line[i] == words[j][0] && i + words[j].size() - 1 < line.size())
            {
                bool match{true};
                for (std::size_t k{1}; k < words[j].size(); ++k)
                {
                    if (line[i + k] != words[j][k])
                    {
                        match = false;
                        break;
                    }
                }
                if (match) return {i, digits[j]};
            }
        }
    }
    return {std::string::npos, -1};
}

PosDigit findLastWordDigit(const std::string& line)
{
    if (line.empty()) return {std::string::npos, -1};

    const std::array<std::string, 9> words{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    constexpr std::array<char, 9> digits{'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (std::size_t i{line.size() - 2}; i < line.size(); --i)
    {
        for (std::size_t j{}; j < words.size(); ++j)
        {
            if (line[i] == words[j][0] && i + words[j].size() - 1 < line.size())
            {
                bool match{true};
                for (std::size_t k{1}; k < words[j].size(); ++k)
                {
                    if (line[i + k] != words[j][k])
                    {
                        match = false;
                        break;
                    }
                }
                if (match) return {i + words[j].size(), digits[j]};
            }
        }
    }
    return {std::string::npos, -1};
}

void GetCalibrationSum(const bool isPart2)
{
    std::ifstream file{"../input.txt"};

    std::string line;
    int total{};
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        PosDigit wordPos{findFirstWordDigit(line)};
        std::stringstream ss{};
        auto pos{line.find_first_of("0123456789")};
        if (isPart2 && wordPos.pos < pos)
        {
            ss << wordPos.digit;
        } else
        {
            ss << line[pos];
        }
        wordPos = findLastWordDigit(line);
        pos = line.find_last_of("0123456789");
        if (isPart2 && (pos == std::string::npos || (wordPos.pos != std::string::npos && wordPos.pos > pos)))
        {
            ss << wordPos.digit;
        } else
        {
            ss << line[pos];
        }
        int value{};
        ss >> value;
        total += value;
    }

    std::cout << total << std::endl;
}

int main(int, char**)
{
    GetCalibrationSum(true);
}
