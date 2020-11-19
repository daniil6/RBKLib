#include "read_dir.h"

#include <dirent.h>

std::vector<std::string> ReadDir(const char openDir[])
{
    DIR* dir;
    struct dirent* ent;
    std::vector<std::string> result;

    if((dir = opendir(&openDir[0])) != NULL) {
        /* list all the files and directories within directory */

        while((ent = readdir(dir)) != NULL)
            result.push_back(ent->d_name);
        closedir(dir);
    }

    /* could not open directory, if result empty*/
    return result;
}