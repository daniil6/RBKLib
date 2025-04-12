#include "parse_stream.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> parseStream(std::basic_istream<char>& stream, const char& delimiter = ' ')
{
    std::string line;
    std::vector<std::string> tokens;

    std::getline(stream, line);
    std::stringstream ss(line);

    while(std::getline(ss, line, delimiter))
        if(line.empty() == false)
            tokens.emplace_back(line);

    return tokens;
}

template <class T> std::vector<T> parseStream(std::basic_istream<char>& stream)
{
    T value;
    std::string line;
    std::vector<T> tokens;

    std::getline(stream, line);
    std::stringstream ss(line);

    while(ss >> value)
        tokens.emplace_back(value);

    return tokens;
}

template <class T> int parseStream(std::basic_istream<char>& stream, std::vector<T>& tokens)
{
    T value;
    std::string line;

    std::getline(stream, line);
    std::stringstream ss(line);

    tokens.clear();

    while(ss >> value)
        tokens.emplace_back(value);

    return tokens.size();
}

void read_stream()
{
    {
        std::vector<double> tokens_file;
        std::ifstream file("in.txt");
        while(file.eof() == false) {
            auto tokens = parseStream<double>(file);
            if(tokens.empty() == false) {
                tokens_file.insert(tokens_file.end(), tokens.begin(), tokens.end());
            }
        }
        file.close();
    }

    {
        auto vec = parseStream(std::cin, ';');
    }
}