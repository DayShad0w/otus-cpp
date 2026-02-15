#include "lib.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    auto start = 0U;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void print_ip(const std::vector<int> &ip) {
    for (std::size_t i = 0; i < ip.size(); ++i) {
        std::cout << ip[i] << (i == ip.size() - 1 ? "" : ".");
    }
    std::cout << std::endl;
}

int main(int /*argc*/, char const */*argv*/[])
{
    try
    {
        std::vector<std::vector<int>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            if (line.empty()) continue;

            auto v = split(line, '\t');
            auto ip_parts = split(v.at(0), '.');
            
            std::vector<int> ip_bytes;
            for (const auto& s : ip_parts) {
                ip_bytes.push_back(std::stoi(s));
            }
            ip_pool.push_back(ip_bytes);
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](const auto &a, const auto &b) {
            return a > b; 
        });

        // ALL
        for (const auto &ip : ip_pool) {
            print_ip(ip);
        }

        // 2. First byte (1)
        for (const auto &ip : ip_pool) {
            if (ip[0] == 1) {
                print_ip(ip);
            }
        }

        // 3. First (46) second (70) 
        for (const auto &ip : ip_pool) {
            if (ip[0] == 46 && ip[1] == 70) {
                print_ip(ip);
            }
        }

        // 4. Any byte 46
        for (const auto &ip : ip_pool) {
            bool found = false;
            for (auto byte : ip) {
                if (byte == 46) {
                    found = true;
                    break;
                }
            }
            if (found) {
                print_ip(ip);
            }
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

