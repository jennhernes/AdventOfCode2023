#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream file{"../input.txt"};
    std::string line;
    std::vector<int> cardCopies{0};
    std::vector<int> winning{};
    int total{};

    int currentCard;
    int cardValue;
    int numWinningNumbers;
    int n;
    int totalCopies; // first card is at index 1
    std::stringstream ss;
    while (getline(file, line))
    {
        if (line.empty()) continue;

        ss.clear();
        ss << line;
        ss >> line; // skip card
        ss >> line;
        currentCard = stoi(line.substr(0, line.size() - 1));
        if (cardCopies.size() <= currentCard) cardCopies.push_back(0);
        cardCopies[currentCard]++;
        winning.clear();
        while (ss >> line)
        {
            if (line == "|") break;
            winning.push_back(std::stoi(line));
        }
        cardValue = 0;
        numWinningNumbers = 0;
        while (ss >> line)
        {
            n = std::stoi(line);
            auto pos = std::find(winning.begin(), winning.end(), n);
            if (pos != winning.end())
            {
                ++numWinningNumbers;
                cardValue = cardValue == 0 ? 1 : cardValue * 2;
            }
        }
        for (int i{1}; i < numWinningNumbers + 1; ++i)
        {
            if (cardCopies.size() <= currentCard + i) cardCopies.push_back(0);
            cardCopies[currentCard + i] += cardCopies[currentCard];
        }
        total += cardValue;
    }
    totalCopies = 0;
    for (int i{}; i < currentCard + 1; ++i)
    {
        totalCopies += cardCopies[i];
    }
    std::cout << totalCopies << " " << total << '\n';
}
