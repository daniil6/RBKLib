#include <fstream>

std::string ReadFileS(std::string line)
{
    setlocale(LC_ALL, "Russian");

    std::ifstream in(line); // Open file for read
    if(in.is_open())
        getline(in, line);

    in.close(); // Close file

    return line;
}