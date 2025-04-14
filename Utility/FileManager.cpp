#include "FileManager.h"

#include "DxLib.h"

FileManager* FileManager::Instance = nullptr;

 FileManager* FileManager::GetInstance()
 {
	// インスタンスが生成されていない場合、生成する
	if (Instance == nullptr)
	{
		Instance = new FileManager();
	}
	// インスタンスのポインタを返却する
	return Instance;
}

const char* FileManager::Const_GetsFile(int offset)
{
	FileRead_gets(String, offset, Handle);
	return String;
}

int FileManager::OpenFile(const char Title[])
{
	Handle =
		FileRead_open(Title);

	return Handle;
}

void FileManager::CloseFile()
{
	FileRead_close(Handle);
	Handle = NULL;
}

void FileManager::SeekFile(int offset)
{
	FileRead_seek(Handle, offset, SEEK_CUR);
}


char* FileManager::GetsFile(int offset)
{
	FileRead_gets(String, offset, Handle);
	return String;
}

int FileManager::GetcFile()
{
	return FileRead_getc(Handle);
}

int FileManager::SizeFile(const char Title[])
{
	return (int)FileRead_size(Title);
}

int FileManager::File(int order, int offset, const char Title[])
{
	switch (order)
	{
	case FOPEN:
		OpenFile(Title);
		return Handle;
		break;
	case FCLOSE:
		CloseFile();
		return NULL;
		break;
	case FSEEK:
		SeekFile(offset);
		return NULL;
		break;
	case FGETC:
		return GetcFile();
		break;
	case FSIZE:
		return SizeFile(Title);
		break;
	}
	return NULL;
}
char* FileManager::File_Call(int order, int offset) {
	switch (order)
	{
	case FGETS:
		return GetsFile(offset);
		break;
	}
	return nullptr;
}