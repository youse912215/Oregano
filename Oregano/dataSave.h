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

	vector<int> currentPossessionItem; //現在までの所持アイテム格納用
	vector<int> lastTimePossessionItem; //前回までの所持アイテム格納用
	string possessionItemData; //所持アイテムデータのバイナリファイル

	vector<int> currentPossessionAccessory; //現在までの所持アクセサリー格納用
	vector<int> lastTimePossessionAccessory; //前回までの所持アクセサリー格納用
	string possessionAccessoryData; //所持アクセサリーデータのバイナリファイル

	vector<int> currentPossessionJewel; //現在までの所持ジュエル格納用
	vector<int> lastTimePossessionJewel; //前回までの所持ジュエル格納用
	string possessionJewelData; //所持ジュエルデータのバイナリファイル

	vector<int> currentPossessionMineral; //現在までの所持鉱物格納用
	vector<int> lastTimePossessionMineral; //前回までの所持鉱物格納用
	string possessionMineralData; //所持鉱物データのバイナリファイル

	vector<int> currentCoin; //現在までのフィールドコイン格納用
	vector<int> lastTimeCoin; //前回までのフィールドコイン格納用
	string coinData; //フィールドコインデータのバイナリファイル

	vector<int> currentItem; //現在までのフィールドアイテム格納用
	vector<int> lastTimeItem; //前回までのフィールドアイテム格納用
	string itemData; //フィールドアイテムデータのバイナリファイル

	vector<int> currentAccessory; //現在までのフィールドアクセサリー格納用
	vector<int> lastTimeAccessory; //前回までのフィールドアクセサリー格納用
	string accessoryData; //フィールドアクセサリーデータのバイナリファイル

	vector<int> currentJewel; //現在までのフィールドジュエル格納用
	vector<int> lastTimeJewel; //前回までのフィールドジュエル格納用
	string jewelData; //フィールドジュエルデータのバイナリファイル

	vector<int> currentMineral; //現在までのフィールド鉱物格納用
	vector<int> lastTimeMineral; //前回までのフィールド鉱物格納用
	string mineralData; //フィールド鉱物データのバイナリファイル

	int getFileSize(string fileName);

	void writeBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName);
	void roadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName);

	void getCurrentStatus();
	void getLastTimeStatus();

	void getCurrentEvent(vector<int>& currentEvent, vector<int>& saveLocation);
	void getLastTimeEvent(vector<int>& lastTimeEvent, vector<int>& saveLocation);

public:
	DataSave(Player& player, EventField& field);
	~DataSave();


	void writeSaveData();
	void roadSaveData();


	void update();
};
