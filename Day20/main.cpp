#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

enum ModuleType
{
    flipFlop,
    conjunction,
    broadcast,
};

struct Module
{
    ModuleType type{};
    std::string state{};
    std::vector<std::array<std::string, 2>> inputs{};
    std::vector<std::string> destinations{};
};

const std::string ON{"on"};
const std::string OFF{"off"};
const std::string HIGH{"high"};
const std::string LOW{"low"};

int main()
{
    std::ifstream file{"../input.txt"};
    std::string line;
    std::stringstream ss;
    std::map<std::string, Module> modules{};
    while (std::getline(file, line))
    {
        if (line.empty()) break;
        ss.clear();
        ss << line;
        ss >> line;
        std::string label{line.substr(1)};
        ModuleType type;
        if (line[0] == '%')
        {
            type = flipFlop;
        } else if (line[0] == '&')
        {
            type = conjunction;
        } else
        {
            label = line;
            type = broadcast;
        }

        ss >> line;
        std::vector<std::string> destinations{};
        while (ss >> line)
        {
            if (std::ranges::find(line, ',') != line.end())
            {
                line = line.substr(0, line.size() - 1);
            }
            destinations.push_back(line);
        }
        modules[label] = {type, OFF, {}, destinations};
    }

    for (const auto& kvp: modules)
    {
        // std::cout << kvp.first << ": " << kvp.second.type << ", " << kvp.second.state << ", ";
        for (const auto& d: kvp.second.destinations)
        {
            // std::cout << d << " ";
            if (modules[d].type == conjunction)
            {
                modules[d].inputs.push_back(std::array<std::string, 2>{kvp.first, "low"});
            }
        }
        // std::cout << '\n';
    }

    int low{};
    int high{};
    // for (int j{}; j < 1000; ++j)
    int j{};
    bool success {false};
    while (!success)
    {
        std::vector pulses{std::array<std::string, 3>{"button", LOW, "broadcaster"}};
        while (!pulses.empty())
        {
            std::array<std::string, 3> pulse = pulses[0];
            if (pulse[1] == LOW) ++low;
            else ++high;
            if (pulse[1] == LOW && pulse[2] == "rx")
            {
                success = true;
                std::cout << j << '\n';
                break;
            }
            pulses.erase(pulses.begin());
            if (!modules.contains(pulse[2])) continue;
            Module& module = modules[pulse[2]];
            if (module.type == broadcast)
            {
                for (const auto& d: module.destinations)
                {
                    pulses.push_back(std::array{pulse[2], pulse[1], d});
                }
            } else if (module.type == flipFlop)
            {
                if (pulse[1] == HIGH) continue;
                if (module.state == OFF)
                {
                    module.state = ON;
                    for (const auto& d: module.destinations)
                    {
                        pulses.push_back(std::array{pulse[2], HIGH, d});
                    }
                } else
                {
                    module.state = OFF;
                    for (const auto& d: module.destinations)
                    {
                        pulses.push_back(std::array{pulse[2], LOW, d});
                    }
                }
            } else
            {
                auto index = std::ranges::find_if(module.inputs,
                    [&](const auto arr) { return arr[0] == pulse[0]; }) - module.inputs.begin();
                module.inputs[index][1] = pulse[1];
                std::string newPulse {LOW};
                for (int i {}; i < module.inputs.size(); ++i)
                {
                    if (module.inputs[i][1] == LOW)
                    {
                        newPulse = HIGH;
                        break;
                    }
                }
                for (const auto& d : module.destinations)
                {
                    pulses.push_back(std::array{pulse[2], newPulse, d});
                }
            }
        }
        ++j;
    }
    std::cout << low*high << '\n';
}
