#include "dataSave.h"
#include "mapDraw.h"
#include "constant.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(Player& player, EventField& field, DataText& text)
	: player(player), field(field), text(text),
	  currentStatus(STATUS_INFORMATION_SIZE), //ステータス
	  /* 所持品 */
	  currentPossessionItem(PLAYER_ITEM_SIZE), currentPossessionAccessory(PLAYER_ACCESSORY_SIZE),
	  currentPossessionJewel(PLAYER_JEWEL_SIZE), currentPossessionMineral(PLAYER_MINERAL_SIZE),
	  /* フィールド */
	  currentCoin(COIN_INFORMATION_SIZE), currentItem(ITEM_INFORMATION_SIZE),
	  currentAccessory(ACCESSORY_INFORMATION_SIZE), currentJewel(JEWEL_INFORMATION_SIZE),
	  currentMineral(MINERAL_INFORMATION_SIZE), roadItemText(120) {
	statusData = "resource\\Data\\statusData.bin"; //ステータス
	/* 所持品 */
	possessionItemData = "resource\\Data\\possessionItemData.bin";
	possessionAccessoryData = "resource\\Data\\possessionAccessoryData.bin";
	possessionJewelData = "resource\\Data\\possessionJewelData.bin";
	possessionMineralData = "resource\\Data\\possessionMineralData.bin";
	/*　フィールド */
	coinData = "resource\\Data\\coinData.bin";
	itemData = "resource\\Data\\itemData.bin";
	accessoryData = "resource\\Data\\accessoryData.bin";
	jewelData = "resource\\Data\\jewelData.bin";
	mineralData = "resource\\Data\\mineralData.bin";

	itemTextData = "resource\\Data\\itemTextLengthData.bin";
}

DataSave::~DataSave() {
}

/// <summary>
/// ファイルサイズを取得
/// </summary>
/// <param name="fName">ファイルの名前</param>
int DataSave::getFileSize(string fileName) {
	ifstream fileRoad(fileName, ifstream::ate);
	size_t fileSize = static_cast<size_t>(fileRoad.tellg());
	return fileSize;
}

/// <summary>
/// バイナリファイルの書き込み
/// </summary>
void DataSave::writeBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName) {
	lastTimeData.clear(); //前回までのデータのクリア

	for (auto& i : currentData)
		lastTimeData.push_back(i); //ステータスを順番に格納

	int sizeOut = lastTimeData.size(); //ベクター配列のサイズ数を格納

	/* バイナリファイル書き込み */
	ofstream fileWrite(fileName, ios::binary);
	if (!fileWrite) return;

	fileWrite.write(reinterpret_cast<char*>(&lastTimeData[0]),
	                static_cast<std::streamsize>(sizeof(int)) * sizeOut);
	fileWrite.close(); //閉じる
}

/// <summary>
/// バイナリファイルの読み込み
/// </summary>
void DataSave::roadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName) {
	/* バイナリファイル読み込み */
	ifstream fileRead(fileName, ios::binary);
	if (!fileRead) return;

	vector<char> binChar(getFileSize(fileName)); //サイズを取得
	if (!fileRead.read(&binChar[0], getFileSize(fileName))) return;
	fileRead.close(); //閉じる

	/* 16進数を10進数に変換し、出力配列に格納 */
	for (unsigned int i = 0; i < currentData.size(); ++i)
		lastTimeData.push_back((binChar[i * 4] & 0xff)
			+ static_cast<int>((binChar[i * 4 + 1] & 0xff) * pow(16, 2)));
}

/// <summary>
/// 現在までのプレイヤーのステータスを取得
/// </summary>
void DataSave::getCurrentStatus() {
	for (unsigned int i = 0; i <= BARGAINING_POWER; ++i)
		currentStatus[i] = player.status[i];
	currentStatus[CURRENT_MAP_X] = MapDraw::mapX; //現在のマップx座標を代入
	currentStatus[CURRENT_MAP_Y] = MapDraw::mapY; //現在のマップy座標を代入
}

/// <summary>
/// 前回までのプレイヤーのステータスを取得
/// </summary>
void DataSave::getLastTimeStatus() {
	for (unsigned int i = 0; i <= BARGAINING_POWER; ++i)
		player.status[i] = lastTimeStatus[i];
	MapDraw::mapX = lastTimeStatus[CURRENT_MAP_X]; //前回までのマップx座標を代入
	MapDraw::mapY = lastTimeStatus[CURRENT_MAP_Y]; //前回までのマップy座標を代入
}

/// <summary>
/// 現在までのフィールドイベント状況を取得
/// </summary>
/// <param name="currentEvent">現在までのイベント</param>
/// <param name="saveLocation">フィールドイベント</param>
void DataSave::getCurrentEvent(vector<int>& currentEvent, vector<int>& saveLocation) {
	for (unsigned int i = 0; i < currentEvent.size(); ++i)
		currentEvent[i] = saveLocation[i];
}

/// <summary>
/// 前回までのフィールドイベント状況を取得
/// </summary>
/// <param name="lastTimeEvent">前回までのイベント</param>
/// <param name="saveLocation">フィールドイベント</param>
void DataSave::getLastTimeEvent(vector<int>& lastTimeEvent, vector<int>& saveLocation) {
	for (unsigned int i = 0; i < lastTimeEvent.size(); ++i)
		saveLocation[i] = lastTimeEvent[i];
}

/// <summary>
/// セーブデータの書き込み
/// </summary>
void DataSave::writeSaveData() {
	/* ステータス */
	getCurrentStatus();
	writeBinaryFile(currentStatus, lastTimeStatus, statusData);

	/* 所持アイテム */
	getCurrentEvent(currentPossessionItem, player.possessionItem);
	writeBinaryFile(currentPossessionItem, lastTimePossessionItem, possessionItemData);
	/* 所持アクセサリー */
	getCurrentEvent(currentPossessionAccessory, player.possessionAccessory);
	writeBinaryFile(currentPossessionAccessory, lastTimePossessionAccessory, possessionAccessoryData);
	/* 所持ジュエル */
	getCurrentEvent(currentPossessionJewel, player.possessionJewel);
	writeBinaryFile(currentPossessionJewel, lastTimePossessionJewel, possessionJewelData);
	/* 所持ジュエル */
	getCurrentEvent(currentPossessionMineral, player.possessionMineral);
	writeBinaryFile(currentPossessionMineral, lastTimePossessionMineral, possessionMineralData);

	/* フィールドコイン */
	getCurrentEvent(currentCoin, field.coin);
	writeBinaryFile(currentCoin, lastTimeCoin, coinData);
	/* フィールドアイテム */
	getCurrentEvent(currentItem, field.item);
	writeBinaryFile(currentItem, lastTimeItem, itemData);
	/* フィールドアクセサリー */
	getCurrentEvent(currentAccessory, field.accessory);
	writeBinaryFile(currentAccessory, lastTimeAccessory, accessoryData);
	/* フィールドジュエル */
	getCurrentEvent(currentJewel, field.jewel);
	writeBinaryFile(currentJewel, lastTimeJewel, jewelData);
	/* フィールド鉱物 */
	getCurrentEvent(currentMineral, field.mineral);
	writeBinaryFile(currentMineral, lastTimeMineral, mineralData);
}

/// <summary>
/// セーブデータの読み込み
/// </summary>
void DataSave::roadSaveData() {
	/* ステータス */
	roadBinaryFile(currentStatus, lastTimeStatus, statusData);
	getLastTimeStatus();

	/* 所持アイテム */
	roadBinaryFile(currentPossessionItem, lastTimePossessionItem, possessionItemData);
	getLastTimeEvent(lastTimePossessionItem, player.possessionItem);
	/* 所持アクセサリー */
	roadBinaryFile(currentPossessionAccessory, lastTimePossessionAccessory, possessionAccessoryData);
	getLastTimeEvent(lastTimePossessionAccessory, player.possessionAccessory);
	/* 所持ジュエル */
	roadBinaryFile(currentPossessionJewel, lastTimePossessionJewel, possessionJewelData);
	getLastTimeEvent(lastTimePossessionJewel, player.possessionJewel);
	/* 所持鉱物 */
	roadBinaryFile(currentPossessionMineral, lastTimePossessionMineral, possessionMineralData);
	getLastTimeEvent(lastTimePossessionMineral, player.possessionMineral);

	/* フィールドコイン */
	roadBinaryFile(currentCoin, lastTimeCoin, coinData);
	getLastTimeEvent(lastTimeCoin, field.coin);
	/* フィールドアイテム */
	roadBinaryFile(currentItem, lastTimeItem, itemData);
	getLastTimeEvent(lastTimeItem, field.item);
	/* フィールドアクセサリー */
	roadBinaryFile(currentAccessory, lastTimeAccessory, accessoryData);
	getLastTimeEvent(lastTimeAccessory, field.accessory);
	/* フィールドジュエル */
	roadBinaryFile(currentJewel, lastTimeJewel, jewelData);
	getLastTimeEvent(lastTimeJewel, field.jewel);
	/* フィールド鉱物 */
	roadBinaryFile(currentMineral, lastTimeMineral, mineralData);
	getLastTimeEvent(lastTimeMineral, field.mineral);

	roadBinaryFile(roadItemText, OutputItemText, itemTextData);
	getLastTimeEvent(OutputItemText, text.textBox);


}

/// <summary>
/// 更新処理
/// </summary>
void DataSave::update() {

}
