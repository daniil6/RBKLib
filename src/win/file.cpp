#include "win/file.h"

CFile::CFile()
{
}

CFile::~CFile()
{
}

DIR* CFile::OpenDir(const char* nameDir)
{
    return opendir(nameDir);
}

const char* CFile::ReadDir(DIR* dir)
{
    struct dirent* ent = readdir(dir);
    if(ent != nullptr)
        return ent->d_name;
    return nullptr;
}

void CFile::CloseDir(DIR* dir)
{
    closedir(dir);
}

void CFile::OpenDirLmb(const char* nameDir, void (*func)(const char*))
{
    DIR* dir = nullptr;
    struct dirent* ent = nullptr;
    char* nameFile = nullptr;

    dir = opendir(nameDir);
    if(dir != nullptr && func != nullptr) {
        while((ent = readdir(dir)) != nullptr) {
            nameFile = ent->d_name;
            if(strcmp(nameFile, ".") != false || strcmp(nameFile, "..") != false)
                func(nameFile);
        }

        closedir(dir);
    }
}

#if defined(STRING) && defined(VECTOR)
std::vector<std::string> CFile::ReadDirVec(const char* nameDir)
{
    DIR* dir;
    struct dirent* ent;
    std::vector<std::string> result;

    if((dir = opendir(nameDir)) != NULL) {

        while((ent = readdir(dir)) != NULL)
            result.push_back(ent->d_name);
        closedir(dir);
    }

    return result;
}
#endif

int CFile::CreateWriteFile(const char* nameFile, const char* data, const int& size)
{
    HANDLE handle = 0;

    DWORD error = 0;
    DWORD bytesWriter = 0;
    WINBOOL result = false;

    try {

        handle = CreateFile(nameFile, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if(handle == INVALID_HANDLE_VALUE)
            throw GetLastError();

        result = WriteFile(handle, data, size, &bytesWriter, nullptr);
        if(result == false || size != bytesWriter)
            throw GetLastError();

    } catch(DWORD error) {
        error = error;
    }

    CloseHandle(handle);
    return error;
}

int CFile::OpenReadFile(const char* nameFile, char* data, int& size)
{
    HANDLE handle = 0;

    DWORD error = 0;
    DWORD bytesReader = 0;
    bool result = false;

    try {

        handle = CreateFile(nameFile, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if(handle == INVALID_HANDLE_VALUE)
            throw GetLastError();

        result = ReadFile(handle, data, size, &bytesReader, nullptr);
        size = bytesReader;
        if(result == false) // || size != bytesReader)
            throw GetLastError();

    } catch(DWORD exc) {
        error = exc;
    }

    CloseHandle(handle);
    return error;
}
