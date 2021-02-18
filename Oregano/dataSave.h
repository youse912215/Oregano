#pragma once
#include "eventBase.h"
#include "player.h"
#include <vector>
#include <string>

using namespace std;

class DataSave {
private:
	EventBase& position;
	Player& player;

	vector<int> statusData; //ステータス格納
	vector<int> vecOut; //格納先の配列
	string saveDataFile; //セーブデータのバイナリファイル
	string eventFieldData;

	int getFileSize(string fName);
	void getCurrentStatus();

public:
	DataSave(EventBase& event, Player& player);
	~DataSave();

	void writeBinaryFile();
	void roadBinaryFile();
	void update();
};
