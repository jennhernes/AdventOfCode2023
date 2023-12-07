#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct Hand
{
    std::string hand;
    int bid;

    Hand(const std::string_view hand, const int bid) : hand{hand}, bid{bid} {}
};

bool containsFiveOfAKind(const std::string_view hand)
{
    return (hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
        && (hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
        && (hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
        && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
        && (hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
        && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
        && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
        && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J'))
        && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J'))
        && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J'));
}

bool containsFourOfAKind(const std::string_view hand)
{
    return ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J')))
        || ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J')))
        || ((hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J')));
}

bool containsFullHouse(const std::string_view hand)
{
    return ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J')))
        || ((hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J'))
            && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J')))
        || ((hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J'))
            && (hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J')))
        || ((hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J'))
            && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J')))
        || ((hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J'))
            && (hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J')))
        || ((hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J'))
            && (hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J')))
        || ((hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J'))
            && (hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J')));
}

bool containsThreeOfAKind(const std::string_view hand)
{
    return ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J')))
        || ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J')))
        || ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J')))
        || ((hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J')))
        || ((hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J')))
        || ((hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J')))
        || ((hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J')))
        || ((hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J')));
}

bool containsTwoPairs(const std::string_view hand)
{
    return ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J')))
        || ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J')))
        || ((hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J')))
        || ((hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J')))
        || ((hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J')))
        || ((hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J')))
        || ((hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J')))
        || ((hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
            && (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J')))
        || ((hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
            && (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J')))
        || ((hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
            && (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J')));
}

bool containsOnePair(const std::string_view hand)
{
    return (hand[0] == hand[1] || (hand[0] == 'J' || hand[1] == 'J'))
        || (hand[0] == hand[2] || (hand[0] == 'J' || hand[2] == 'J'))
        || (hand[0] == hand[3] || (hand[0] == 'J' || hand[3] == 'J'))
        || (hand[0] == hand[4] || (hand[0] == 'J' || hand[4] == 'J'))
        || (hand[1] == hand[2] || (hand[1] == 'J' || hand[2] == 'J'))
        || (hand[1] == hand[3] || (hand[1] == 'J' || hand[3] == 'J'))
        || (hand[1] == hand[4] || (hand[1] == 'J' || hand[4] == 'J'))
        || (hand[2] == hand[3] || (hand[2] == 'J' || hand[3] == 'J'))
        || (hand[2] == hand[4] || (hand[2] == 'J' || hand[4] == 'J'))
        || (hand[3] == hand[4] || (hand[3] == 'J' || hand[4] == 'J'));
}

int main()
{
    std::ifstream file{"../input.txt"};

    std::vector<Hand> fiveKinds{};
    std::vector<Hand> fourKinds{};
    std::vector<Hand> fullHouses{};
    std::vector<Hand> threeKinds{};
    std::vector<Hand> twoPairs{};
    std::vector<Hand> onePairs{};
    std::vector<Hand> highCards{};

    auto compareHands = [](const Hand& x, const Hand& y)
    {
        for (int i{}; i < 5; ++i)
        {
            if (x.hand[i] == y.hand[i]) continue;

            if (x.hand[i] == 'A') return false;
            if (y.hand[i] == 'A') return true;
            if (x.hand[i] == 'K') return false;
            if (y.hand[i] == 'K') return true;
            if (x.hand[i] == 'Q') return false;
            if (y.hand[i] == 'Q') return true;
            if (x.hand[i] == 'T') return false;
            if (y.hand[i] == 'T') return true;

            if (x.hand[i] == 'J') return true;
            if (y.hand[i] == 'J') return false;
            return x.hand[i] < y.hand[i];
        }
        return true;
    };

    std::string line;
    std::stringstream ss;
    std::string hand;
    int n;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        ss.clear();
        ss << line;
        ss >> hand;
        ss >> n;

        if (containsFiveOfAKind(hand))
        {
            fiveKinds.push_back({Hand(hand, n)});
        }
        else if (containsFourOfAKind(hand))
        {
            fourKinds.push_back({Hand(hand, n)});
        }
        else if (containsFullHouse(hand))
        {
            fullHouses.push_back({Hand(hand, n)});
        }
        else if (containsThreeOfAKind(hand))
        {
            threeKinds.push_back({Hand(hand, n)});
        }
        else if (containsTwoPairs(hand))
        {
            twoPairs.push_back({Hand(hand, n)});
        }
        else if (containsOnePair(hand))
        {
            onePairs.push_back({Hand(hand, n)});
        }
        else
        {
            highCards.push_back({Hand(hand, n)});
        }
    }

    std::ranges::sort(fiveKinds, compareHands);
    std::ranges::sort(fourKinds, compareHands);
    std::ranges::sort(fullHouses, compareHands);
    std::ranges::sort(threeKinds, compareHands);
    std::ranges::sort(twoPairs, compareHands);
    std::ranges::sort(onePairs, compareHands);
    std::ranges::sort(highCards, compareHands);

    int total {};
    int rank {1};
    for (const auto& h : highCards)
    {
        total += h.bid * rank;
        ++rank;
    }
    for (const auto& h : onePairs)
    {
        total += h.bid * rank;
        ++rank;
    }
    for (const auto& h : twoPairs)
    {
        total += h.bid * rank;
        ++rank;
    }
    for (const auto& h : threeKinds)
    {
        total += h.bid * rank;
        ++rank;
    }
    for (const auto& h : fullHouses)
    {
        total += h.bid * rank;
        ++rank;
    }
    for (const auto& h : fourKinds)
    {
        total += h.bid * rank;
        ++rank;
    }
    for (const auto& h : fiveKinds)
    {
        total += h.bid * rank;
        ++rank;
    }

    std::cout << total << '\n';
}
