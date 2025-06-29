#include "file.h"

CFile::CFile()
{
}

CFile::~CFile()
{
}

FileResult CFile::RenameFile(const char* old_path, const char* new_path)
{
	int result = rename(old_path, new_path);
	if(result < 0)
		return FileResult::RenameFile;

	return FileResult::Success;
}

FileResult CFile::RemoveFile(const char* path)
{
	int result = remove(path);
	if(result < 0)
		return FileResult::RemoveFile;

	return FileResult::Success;
}


FileResult CFile::CreateWriteFile(const char* path, const uint8_t* data, const int& size)
{
	int result = 0;
	int header = 0;

#ifdef UNIX
	header = open(path, O_CREAT | O_EXCL | O_RDWR | O_CLOEXEC);
#endif // UNIX

#ifdef WIN32
    header = open(path, O_CREAT | O_EXCL | O_RDWR);
#endif // WIN32

	if(header < 0) {
		// perror(path);
		return FileResult::CreateFile;
	}

	result = write(header, data, size);
	if(result < 0) {
		perror(path);
		return FileResult::WriteFile;
	}

	result = close(header);
	if(result < 0) {
		perror(path);
		return FileResult::CloseFile;
	}

	return FileResult::Success;
}

FileResult CFile::OpenReadFile(const char* path, uint8_t* data, int& size)
{
	int result = 0;
	int header = 0;

#ifdef UNIX
    header = open(path, O_EXCL | O_RDWR | O_CLOEXEC);
#endif // UNIX

#ifdef WIN32
    header = open(path, O_EXCL | O_RDWR);
#endif // WIN32

	if(header < 0) {
		// perror(path);
		return FileResult::OpenFile;
	}

	size = read(header, data, size);
	if(size < 0) {
		perror(path);
		return FileResult::ReadFile;
	}

	result = close(header);
	if(result < 0) {
		perror(path);
		return FileResult::CloseFile;
	}

	return FileResult::Success;
}
