#ifndef CFILE_H
#define CFILE_H

#include <dirent.h>
#include <windows.h>

#if defined(STRING) && defined(VECTOR)
#include <string>
#include <vector>
#endif

#define FILE_EMPTY 1

class CFile
{
public:
    CFile();
    ~CFile();

    /**
     * @brief Open dir
     * @param nameDir
     * @return
     */
    static DIR* OpenDir(const char* nameDir);

    /**
     * @brief
     * @param dir
     * @return
     */
    static const char* ReadDir(DIR* dir);

    /**
     * @brief
     * @param dir
     */
    static void CloseDir(DIR* dir);

    /**
     * @brief
     * @param nameDir
     */
    static void OpenDirLmb(const char* nameDir, void (*func)(const char*));

#if defined(STRING) && defined(VECTOR)
    /**
     * @brief
     * @param nameDir
     * @return
     */
    static std::vector<std::string> ReadDirVec(const char* nameDir);
#endif

    // --------------------------------------------------------------------

    static int CreateWriteFile(const char* nameFile, const char* data, const int& size);

    static int OpenReadFile(const char* nameFile, char* data, int& size);
};

#endif // CFILE_H
