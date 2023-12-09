#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>

long long calculateNext(const std::vector<long long>& nums)
{
    if (std::equal(nums.begin(), nums.end() - 1, nums.begin()+1)) return nums[0];
    std::vector<long long> next {};
    for (long long i{1}; i < nums.size(); ++i)
    {
        next.push_back(nums[i]-nums[i-1]);
        std::cout << next[i-1] << " ";
    }
    // std::cout << nums[nums.size() - 1] << " " << '\n';
    return nums[nums.size()-1] + calculateNext(next);
}

long long calculatePrevious(const std::vector<long long>& nums)
{
    if (std::equal(nums.begin(), nums.end(), nums.begin()+1)) return nums[0];
    std::vector<long long> next {};
    for (long long i{0}; i < nums.size() - 1; ++i)
    {
        next.push_back(nums[i+1]-nums[i]);
        std::cout << next[i] << " ";
    }
    std::cout << nums[nums.size() - 1] << " " << '\n';
    return nums[0] - calculatePrevious(next);
}

int main()
{
    std::ifstream file{"../input.txt"};
    std::string line;
    std::stringstream ss;

    std::vector<std::vector<long long>> sequences{};
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        ss.clear();
        ss.str(line);
        long long n;
        std::vector<long long> nums{};
        while (ss >> n)
        {
            nums.push_back(n);
        }
        sequences.push_back(nums);
    }

    long long total{};
    for (auto v : sequences)
    {
        // long long n {calculateNext(v)};
        long long n {calculatePrevious(v)};
        total += n;
        // std::cout << n << " ";
    }
    // std::cout << '\n';

    std::cout << total << '\n';
}
