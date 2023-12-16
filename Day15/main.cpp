#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct Lens
{
    std::string label {};
    int f {};
};

int main()
{
    bool isPart2 {true};
    std::ifstream file {"../input.txt"};
    std::string line;

    int sum{};
    std::array<std::vector<Lens>, 256> boxes {};
    for (int i{}; i < boxes.size(); ++i)
    {
        boxes[i] = {};
    }
    while(std::getline(file, line, ','))
    {
        if (line.empty()) continue;
        int boxNumber{};
        for (auto c : line)
        {
            if (c == '\n')
            {
                line = line.substr(0, line.size()-1);
                break;
            }
            if (isPart2 && (c == '-' || c == '=')) break;
            boxNumber += static_cast<int>(c);
            boxNumber *= 17;
            boxNumber %= 256;
        }
        sum += boxNumber;
        //std::cout << line << ": " << boxNumber << " | ";

        int index {static_cast<int>(std::min(std::ranges::find(line, '=')-line.begin(),
            std::ranges::find(line, '-')-line.begin()))};
        //std::cout << index << " ";
        std::string label {line.substr(0,index)};
        //std::cout << label << " ";
        int lensIndex {static_cast<int>(std::ranges::find_if(boxes[boxNumber],
            [&](const auto lens)
            {
                return lens.label == label;
            })-boxes[boxNumber].begin())};
        //std::cout << lensIndex << " ";
        if (std::ranges::find(line, '-') != line.end())
        {
            if (lensIndex < boxes[boxNumber].size())
            {
                boxes[boxNumber].erase(boxes[boxNumber].begin()+lensIndex);
            }
            //std::cout << " erased ";
        }
        else
        {
            std::stringstream ss {line.substr(index+1)};
            int f;
            ss >> f;
            if (lensIndex < boxes[boxNumber].size())
            {
                boxes[boxNumber][lensIndex].f = f;
            } else
            {
                boxes[boxNumber].push_back({label, f});
            }
            //std::cout << " placed ";
        }
        //std::cout << '\n';
    }

    std::cout << sum << '\n';

    int power{};
    for (int i{}; i < boxes.size(); ++i)
    {
        if (boxes[i].empty()) continue;
        //std::cout << "Box " << i << '\n';
        for (int j{}; j < boxes[i].size(); ++j)
        {
            //std::cout << "[" << boxes[i][j].label << " " << boxes[i][j].f << "] ";
            power += (i+1) * (j+1) * boxes[i][j].f;
        }
        //std::cout << '\n';
    }
    std::cout << power << '\n';
}
