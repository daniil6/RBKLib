#include <fstream>
#include <vector>

std::string ReadFileS(std::string line)
{
    setlocale(LC_ALL, "Russian");

    std::ifstream in(line); // Open file for read
    if(in.is_open())
        getline(in, line);

    in.close(); // Close file

    return line;
}

std::string ReadFileL(std::string line)
{
    setlocale(LC_ALL, "Russian");

    FILE* file;
    file = fopen(&line[0], "r");
    line.clear();

    if(file == nullptr)
        return line;

    char ch = 0;
    while(ch != EOF || feof(file) == false || ferror(file) == true) {
        ch = fgetc(file);
        line.push_back(ch);
    }

    line.pop_back(); // delete last excess symbol // why?
    fclose(file);

    return line;
}

char* ReadFileZ(std::string line, int& size)
{
    std::string t_line = ReadFileL(line);

    size = t_line.size();
    char* result = new char[size];

    for(int i = 0; i < size; i++)
        result[i] = t_line.at(i);

    return result;
}

void ReadFileA()
{
}