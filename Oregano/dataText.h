#pragma once
#include <string>

using namespace std;

class DataText {
private:
	string textFile; //�e�L�X�g�t�@�C��

	string convertStringFromWString(wstring wStr); //wstring->string�ϊ�
	wstring charFromUtf8(); //utf8->wstring�ϊ�

public:
	DataText();
	~DataText();

	void update(); //�X�V����
};
