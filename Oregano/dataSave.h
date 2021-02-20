#pragma once
#include "player.h"
#include "eventField.h"
#include <vector>
#include <string>

using namespace std;

class DataSave {
private:
	Player& player;
	EventField& field;

	vector<int> currentStatus; //現在までのステータス格納用
	vector<int> lastTimeStatus; //前回までのステータス格納用
	string statusData; //セーブデータのバイナリファイル

	vector<int> currentCoin; //現在までのコイン格納用
	vector<int> lastTimeCoin; //前回までのコイン格納用
	string coinData; //コインデータのバイナリファイル

	vector<int> currentItem; //現在までのアイテム格納用
	vector<int> lastTimeItem; //前回までのコイン格納用
	string itemData; //アイテムデータのバイナリファイル

	int getFileSize(string fileName);

	void writeBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName);
	void roadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName);

	void getCurrentStatus();
	void getLastTimeStatus();

	void getCurrentEvent(vector<int>& currentEvent, vector<int>& fieldEvent);
	void getLastTimeEvent(vector<int>& lastTimeEvent, vector<int>& fieldEvent);

public:
	DataSave(Player& player, EventField& field);
	~DataSave();


	void writeSaveData();
	void roadSaveData();


	void update();
};
