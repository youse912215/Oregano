#pragma once
#include <string>
#include <vector>
#include "inputProcess.h"

using namespace std;

class DataText {
private:
	Input& input;

	string textFile; //テキストファイル

	string convertStringFromWString(wstring wStr); //wstring->string変換
	wstring charFromUtf8(); //utf8->wstring変換

	unsigned int defaultColor;
	const int itemFontSize = 40;

	void showItemText();
	void drawString(const int& line);

	int textLine(const int& line);
	int textPosition(const int& line);
	int lineFeed(const int& line);

	void returnGameScene();

public:
	DataText(Input& input);
	~DataText();

	vector<int> textBox;

	void update(); //更新処理
};
