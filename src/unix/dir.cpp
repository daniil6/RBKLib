#include <dir.h>

// ------------------------------------------------------------------------

DirResult CDir::CreateDir(const char* path)
{
    int result = 0;

#ifdef UNIX
    result = mkdir(path, S_IRUSR | S_IWUSR);
#endif // UNIX

#ifdef WIN32
    result = mkdir(path);
#endif // WIN32

	if(result < 0) {
		perror(path);
		return DirResult::CreateDir;
	}

	return DirResult::Success;
}

DIR* CDir::OpenDir(const char* path)
{
	return opendir(path);
}

const char* CDir::GetNameDir(DIR* dp)
{
	struct dirent* dirp = readdir(dp);
	if(dirp == nullptr)
		return nullptr;

	return dirp->d_name;
}

DirResult CDir::CloseDir(DIR* dp)
{
	int result = closedir(dp);
	if(result < 0)
		return DirResult::CloseDir;

	return DirResult::Success;
}
