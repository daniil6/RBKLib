#ifndef CFILE_H
#define CFILE_H

#include <stdint.h>

#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

enum class FileResult : uint8_t {
	Success = 0,

	OpenFile,
	ReadFile,
	WriteFile,
	CloseFile,
	CreateFile,

	RenameFile,
	RemoveFile
};

class CFile
{
public:
	CFile();
	~CFile();

	/**
	 * @brief
	 * @param path
	 * @param data
	 * @param size
	 * @return
	 */
	static FileResult CreateWriteFile(const char* path, const uint8_t* data, const int& size);

	/**
	 * @brief
	 * @param path
	 * @param data
	 * @param size
	 * @return
	 */
	static FileResult OpenReadFile(const char* path, uint8_t* data, int& size);

	static FileResult RenameFile(const char* old_path, const char* new_path);

	static FileResult RemoveFile(const char* path);

};

#endif // CFILE_H
