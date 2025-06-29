#ifndef CDIR_H
#define CDIR_H

#include <dirent.h>

#include <sys/stat.h>

#include <stdint.h>

#include <stdio.h>

enum class DirResult : uint8_t {
	Success = 0,

	OpenDir,
	CloseDir,
	CreateDir
};

class CDir
{
public:
	CDir();
	~CDir();

	static DirResult CreateDir(const char* path);

	//static DirResult RenameFile(const char* old_path, const char* new_path);

	//static DirResult RemoveFile(const char* path);

	static DIR* OpenDir(const char* path);

	static const char* GetNameDir(DIR* dp);

	static DirResult CloseDir(DIR* dp);
};

#endif // CDIR_H
