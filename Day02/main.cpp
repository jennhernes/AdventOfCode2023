#include <array>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

int main() {
    std::ifstream file { "../input.txt" };
    std::string line {};
    int sum {};
    int product {};
    int id {};
    std::string tmp {};
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        line.append(";");
        std::array<int,3> minCubes {};
        std::stringstream ss{line};

        getline(ss, tmp, ' '); // skip "Game"
        int count {};
        while(getline(ss, tmp, ' ')) {
            if (tmp.find(':') != std::string::npos) {
                id = stoi(tmp.substr(0, tmp.size()-1));
                // std::cout << id << ": ";
            } else if (tmp.find(',') != std::string::npos || tmp.find(';') != std::string::npos) {
                std::string colour {tmp.substr(0, tmp.size()-1)};
                // std::cout << count << " " << colour << " ";
                if (colour == "green") {
                    minCubes[0] = std::max(minCubes[0], count);
                } else if (colour == "red") {
                    minCubes[1] = std::max(minCubes[1], count);
                } else if (colour == "blue") {
                    minCubes[2] = std::max(minCubes[2], count);
                }
            } else {
                count = stoi(tmp);
            }
        }
        // std::cout << '\n';
        if (minCubes[0] <= 13 && minCubes[1] <= 12 && minCubes[2] <= 14) {
            sum += id;
        }
        product += minCubes[0] * minCubes[1] * minCubes[2];
    }

    std::cout << sum << " " << product << std::endl;
}
