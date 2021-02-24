#pragma once
#include <string>
#include <vector>
#include "dataSave.h"

using namespace std;

class DataText {
private:
	DataSave& save;

	string textFile; //�e�L�X�g�t�@�C��

	string convertStringFromWString(wstring wStr); //wstring->string�ϊ�
	wstring charFromUtf8(); //utf8->wstring�ϊ�

	unsigned int defaultColor;
	const int itemFontSize = 10;

	void showItemText();
	int textLine(const int& line);

	vector<int> num;

public:
	DataText(DataSave& save);
	~DataText();

	void update(); //�X�V����
};
