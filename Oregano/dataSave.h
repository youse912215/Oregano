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
	vector<int> lastTimeData; //格納先の配列
	string saveDataFile; //セーブデータのバイナリファイル
	string eventFieldData;

	int getFileSize(string fName);

	void writeBinaryFile();
	void roadBinaryFile();
	void getCurrentStatus();
	void getLastTimeStatus();

public:
	DataSave(EventBase& event, Player& player);
	~DataSave();


	void writeSaveData();
	void roadSaveData();


	void update();
};
