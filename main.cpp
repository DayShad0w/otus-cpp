#include "lib.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
//std::vector<std::string> split(const std::string &str, char d)
auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    //std::string::size_type start = 0;
    //std::string::size_type stop = str.find_first_of(d);
    auto start = 0U;
    auto stop = str.find(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


void print_ip(const std::vector<int> &ip) {
    for (auto i = 0; i < ip.size(); ++i) {
        std::cout << ip[i] << (i == ip.size() - 1 ? "" : ".");
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<int>> ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            if (line.empty()) continue;
            
            auto v = split(line, '\t');
            auto parts = split(v.at(0), '.');
            
            std::vector<int> ip;
            for (const auto& p : parts) {
                ip.push_back(std::stoi(p));
            }
            ip_pool.push_back(ip);
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), [](const auto &a, const auto &b) {
            return a > b; 
        });

        // 1. ALL
        //std::cout << "ALL" << std::endl;
        for (const auto &ip : ip_pool) print_ip(ip);

        // 2. First byte 1
        //std::cout << "First byte 1" << std::endl;
        for (const auto &ip : ip_pool) {
            if (ip[0] == 1) print_ip(ip);
        }

        // 3. First 46, second 70
        for (const auto &ip : ip_pool) {
            if (ip[0] == 46 && ip[1] == 70) print_ip(ip);
        }

        // 4. Any byte is 46
        for (const auto &ip : ip_pool) {
            if (std::any_of(ip.begin(), ip.end(), [](int b) { return b == 46; })) {
                print_ip(ip);
            }
        }

    } 
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
/*hide*/
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        // TODO filter by first byte and output
        // ip = filter(1)
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // TODO filter by any byte and output
        // ip = filter_any(46)
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46


}
