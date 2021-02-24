#pragma once
#include <string>
#include <vector>
#include "dataSave.h"

using namespace std;

class DataText {
private:
	DataSave& save;

	string textFile; //テキストファイル

	string convertStringFromWString(wstring wStr); //wstring->string変換
	wstring charFromUtf8(); //utf8->wstring変換

	unsigned int defaultColor;
	const int itemFontSize = 10;

	void showItemText();
	int textLine(const int& line);

	vector<int> num;

public:
	DataText(DataSave& save);
	~DataText();

	void update(); //更新処理
};
