#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    std::ifstream file{"../input.txt"};

    std::string line;
    std::vector<int> cardCopies {0};
    std::vector<int> winning{};
    int total{};
    
    std::string tmp;
    int currentCard;
    int cardValue;
    int numWinningNumbers;
    int n;
    int totalCopies;// first card is at index 1
    while (getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss{line};
        ss >> tmp; // skip card
        ss >> tmp;
        currentCard = stoi(tmp.substr(0, tmp.size() - 1));
        if (cardCopies.size() <= currentCard) cardCopies.push_back(0);
        cardCopies[currentCard]++;
        winning.clear();
        while (ss >> tmp)
        {
            if (tmp == "|") break;
            winning.push_back(std::stoi(tmp));
        }
        cardValue = 0;
        numWinningNumbers = 0;
        while (ss >> tmp)
        {
            n = std::stoi(tmp);
            auto pos = std::ranges::find(winning, n) - winning.begin();
            if (pos != winning.size())
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
