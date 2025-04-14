#pragma once

//|~~Fileの命令文~~|//
#define		FOPEN				1												//ファイルを開く
#define		FCLOSE				2												//ファイルを閉じる
#define		FSEEK				3												//ファイルポイントを変更(現在ポイント位置から)
#define		FGETS				4												//ファイルの1行を読み込む
#define		FGETC				5												//ファイルの1バイトを読み込む
#define		FSIZE				6												//ファイルのサイズを読み込む

//|~~標準設定~~|//
#define		STANDARD_FILEPATH   "Resource/map.txt"								//ここでファイルパスを手動入力する(必須)
#define		STANDARD_LINE_LENGTH 7												//ここで 1 行 の長さを手動入力する(必須)

class FileManager {

private:
	static FileManager* Instance;

public:
	char	String[256];														//描画する際の変数
	int		Handle;																//ファイルのパスを保存する変数/

	static FileManager* GetInstance();

	const char* Const_GetsFile(int offset);

	int File(int order, int offset = STANDARD_LINE_LENGTH, const char Title[] = STANDARD_FILEPATH);
	char* File_Call(int order, int offset);
private:


	int		OpenFile(const char Title[]);										//ファイルを開く
	void	CloseFile();														//ファイルを閉じる
	void	SeekFile(int offset);												//ファイルポイントを変更(現在ポイント位置から)
	char*   GetsFile(int offset);												//ファイルの1行を読み込む
	int		GetcFile();															//ファイルの1バイトを読み込む
	int		SizeFile(const char Title[]);										//ファイルのサイズを読み込む


};