#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Rule
{
    char var{};
    char op{};
    int value{};
    std::string result{};
};

struct Range
{
    std::array<int, 2> x{};
    std::array<int, 2> m{};
    std::array<int, 2> a{};
    std::array<int, 2> s{};
};

unsigned long long getTotalValidCombinations(std::map<std::string, std::vector<Rule>>& workflows)
{
    std::vector x{std::array{1, 4000}};
    std::vector m{std::array{1, 4000}};
    std::vector a{std::array{1, 4000}};
    std::vector s{std::array{1, 4000}};
    for (const auto& kvp: workflows)
    {
        for (int i{}; i < kvp.second.size(); ++i)
        {
            auto r = kvp.second[i];
            if (r.var == 'x')
            {
                for (int j{}; j < x.size(); ++j)
                {
                    if (x[j][0] < r.value && x[j][1] > r.value)
                    {
                        std::array newRange{r.value + 1, x[j][1]};
                        x[j][1] = r.value - 1;
                        if (r.op == '>') ++x[j][1];
                        else --newRange[0];
                        x.insert(x.begin() + j + 1, newRange);
                        break;
                    }
                }
            } else if (r.var == 'm')
            {
                for (int j{}; j < m.size(); ++j)
                {
                    if (m[j][0] < r.value && m[j][1] > r.value)
                    {
                        std::array newRange{r.value + 1, m[j][1]};
                        m[j][1] = r.value - 1;
                        if (r.op == '>') ++m[j][1];
                        else --newRange[0];
                        m.insert(m.begin() + j + 1, newRange);
                        break;
                    }
                }
            } else if (r.var == 'a')
            {
                for (int j{}; j < a.size(); ++j)
                {
                    if (a[j][0] < r.value && a[j][1] > r.value)
                    {
                        std::array newRange{r.value + 1, a[j][1]};
                        a[j][1] = r.value - 1;
                        if (r.op == '>') ++a[j][1];
                        else --newRange[0];
                        a.insert(a.begin() + j + 1, newRange);
                        break;
                    }
                }
            } else if (r.var == 's')
            {
                for (int j{}; j < s.size(); ++j)
                {
                    if (s[j][0] < r.value && s[j][1] > r.value)
                    {
                        std::array newRange{r.value + 1, s[j][1]};
                        s[j][1] = r.value - 1;
                        if (r.op == '>') ++s[j][1];
                        else --newRange[0];
                        s.insert(s.begin() + j + 1, newRange);
                        break;
                    }
                }
            }
        }
    }
    std::vector<Range> validRanges{};
    for (int i{}; i < x.size(); ++i)
    {
        for (int j{}; j < m.size(); ++j)
        {
            for (int k{}; k < a.size(); ++k)
            {
                for (int l{}; l < s.size(); ++l)
                {
                    validRanges.push_back({x[i], m[j], a[k], s[l]});
                }
            }
        }
    }

    unsigned long long result{0};
    std::cout << validRanges.size() << '\n';
    for (int i{}; i < validRanges.size(); ++i)
    {
        if (i % 1000 == 0) std::cout << i << '\n';
        std::string currentWorkflow{"in"};
        while (currentWorkflow != "A" && currentWorkflow != "R")
        {
            if (!workflows.contains(currentWorkflow))
            {
                std::cout << "PANIC! " << currentWorkflow << '\n';
                break;
            }
            for (const auto& r: workflows[currentWorkflow])
            {
                // std::cout << r.var << " " << r.op << " " << r.value << " " << r.result << " | ";
                // std::cout << validRanges[i].x[0] << "-" << validRanges[i].x[1] << " " << validRanges[i].m[0] << "-" <<
                        // validRanges[i].m[1] << " " << validRanges[i].a[0] << "-" << validRanges[i].a[1] << " " <<
                        // validRanges[i].s[0] << "-" << validRanges[i].s[1] << " | ";
                int consider;
                if (r.var == 'x') consider = validRanges[i].x[0];
                else if (r.var == 'm') consider = validRanges[i].m[0];
                else if (r.var == 'a') consider = validRanges[i].a[0];
                else if (r.var == 's') consider = validRanges[i].s[0];
                else
                {
                    currentWorkflow = r.result;
                    // std::cout << r.result << '\n';
                    break;
                }
                // std::cout << consider << " | ";

                if (r.op == '>')
                {
                    if (consider > r.value)
                    {
                        currentWorkflow = r.result;
                        // std::cout << r.result << '\n';
                        break;
                    }
                    // std::cout << '\n';
                    continue;
                } else if (r.op == '<')
                {
                    if (consider < r.value)
                    {
                        currentWorkflow = r.result;
                        // std::cout << r.result << '\n';
                        break;
                    }
                    // std::cout << '\n';
                    continue;
                } else
                {
                    currentWorkflow = r.result;
                    // std::cout << r.result << '\n';
                    break;
                }
                // std::cout << '\n';
            }
        }
        if (currentWorkflow == "A")
        {
            // std::cout << validRanges[i].x[0] << "-" << validRanges[i].x[1] << " " << validRanges[i].m[0] << "-" <<
            //     validRanges[i].m[1] << " " << validRanges[i].a[0] << "-" << validRanges[i].a[1] << " " <<
            //     validRanges[i].s[0] << "-" << validRanges[i].s[1] << "\n";
            result += (validRanges[i].x[1] - validRanges[i].x[0] + 1)
                    * (validRanges[i].m[1] - validRanges[i].m[0] + 1)
                    * (validRanges[i].a[1] - validRanges[i].a[0] + 1)
                    * (validRanges[i].s[1] - validRanges[i].s[0] + 1);
        }
    }
    return result;
}

int main()
{
    std::ifstream file{"../input.txt"};
    std::string line;
    std::stringstream ss{};
    std::stringstream tmp{};
    std::string label{};
    std::map<std::string, std::vector<Rule>> workflows{};

    while (std::getline(file, line))
    {
        if (line.empty()) break;

        ss.clear();
        ss << line;
        std::getline(ss, label, '{');
        workflows[label] = {};
        while (std::getline(ss, line, ':'))
        {
            Rule rule{};
            if (line.find('}') != std::string::npos)
            {
                rule.result = line.substr(0, line.size() - 1);
            } else
            {
                rule.var = line[0];
                rule.op = line[1];
                tmp.clear();
                tmp.str(line.substr(2));
                tmp >> rule.value;
                std::getline(ss, line, ',');
                rule.result = line;
            }
            workflows[label].push_back(rule);
        }
    }

    unsigned long long combinations{getTotalValidCombinations(workflows)};
    std::cout << "Combinations " << combinations << " " << std::to_string(combinations).size() << " " <<
            std::to_string(167409079868000).size() << '\n';
    return 0;

    int total{};
    int x;
    int m;
    int a;
    int s;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        line = line.substr(1, line.size() - 2);
        ss.clear();
        ss << line;
        std::getline(ss, line, ',');
        tmp.clear();
        tmp.str(line.substr(2));
        tmp >> x;
        std::getline(ss, line, ',');
        tmp.clear();
        tmp.str(line.substr(2));
        tmp >> m;
        std::getline(ss, line, ',');
        tmp.clear();
        tmp.str(line.substr(2));
        tmp >> a;
        std::getline(ss, line, ',');
        tmp.clear();
        tmp.str(line.substr(2));
        tmp >> s;

        std::string currentWorkflow{"in"};
        while (currentWorkflow != "A" && currentWorkflow != "R")
        {
            if (!workflows.contains(currentWorkflow))
            {
                std::cout << "PANIC! " << currentWorkflow << '\n';
                break;
            }
            for (const auto& r: workflows[currentWorkflow])
            {
                int consider;
                if (r.var == 'x') consider = x;
                else if (r.var == 'm') consider = m;
                else if (r.var == 'a') consider = a;
                else if (r.var == 's') consider = s;
                else
                {
                    currentWorkflow = r.result;
                    break;
                }

                if (r.op == '>')
                {
                    if (consider > r.value)
                    {
                        currentWorkflow = r.result;
                        break;
                    }
                    continue;
                } else if (r.op == '<')
                {
                    if (consider < r.value)
                    {
                        currentWorkflow = r.result;
                        break;
                    }
                    continue;
                } else
                {
                    currentWorkflow = r.result;
                    break;
                }
            }
        }
        if (currentWorkflow == "A")
        {
            total += x + m + a + s;
        }
    }

    std::cout << total << '\n';
}
