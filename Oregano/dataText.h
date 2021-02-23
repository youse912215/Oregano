#pragma once
#include <string>

using namespace std;

class DataText {
private:
	string textFile; //テキストファイル

	string convertStringFromWString(wstring wStr); //wstring->string変換
	wstring charFromUtf8(); //utf8->wstring変換

public:
	DataText();
	~DataText();

	void update(); //更新処理
};
