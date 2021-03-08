#include "dataSave.h"
#include "mapDraw.h"
#include "constant.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(PlayerState& player)
	: player(player),
	  currentStatus(STATUS_INFORMATION_SIZE) //ステータス
/* 所持品 */
/*currentPossessionItem(PLAYER_ITEM_SIZE), currentPossessionAccessory(PLAYER_ACCESSORY_SIZE),
currentPossessionJewel(PLAYER_JEWEL_SIZE), currentPossessionMineral(PLAYER_MINERAL_SIZE),*/
/* フィールド */
/*currentCoin(COIN_INFORMATION_SIZE), currentItem(ITEM_INFORMATION_SIZE),
currentAccessory(ACCESSORY_INFORMATION_SIZE), currentJewel(JEWEL_INFORMATION_SIZE),
currentMineral(MINERAL_INFORMATION_SIZE), roadItemText(120)*/ {
	statusData = "resource\\Data\\statusData.bin"; //ステータス
	///* 所持品 */
	//possessionItemData = "resource\\Data\\possessionItemData.bin";
	//possessionAccessoryData = "resource\\Data\\possessionAccessoryData.bin";
	//possessionJewelData = "resource\\Data\\possessionJewelData.bin";
	//possessionMineralData = "resource\\Data\\possessionMineralData.bin";
	///*　フィールド */
	//coinData = "resource\\Data\\coinData.bin";
	//itemData = "resource\\Data\\itemData.bin";
	//accessoryData = "resource\\Data\\accessoryData.bin";
	//jewelData = "resource\\Data\\jewelData.bin";
	//mineralData = "resource\\Data\\mineralData.bin";

	//itemTextData = "resource\\Data\\itemTextLengthData.bin";
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
	//現在の各コインを代入
	for (unsigned int i = 0; i != PlayerState::coin.size(); ++i)
		currentStatus[i] = PlayerState::coin[i];
	//現在の属性耐久値を代入
	for (unsigned int i = 0; i != PlayerState::attributeAccumulation.size(); ++i)
		currentStatus[i + PlayerState::coin.size()] = PlayerState::attributeAccumulation[i];
	//現在の戦闘スタイルを代入
	currentStatus[PlayerState::coin.size() + PlayerState::attributeAccumulation.size()] = PlayerState::battleStyle;
	//各マップ座標
	currentStatus[9] = MapDraw::mapX; //現在のマップx座標を代入
	currentStatus[10] = MapDraw::mapY; //現在のマップy座標を代入
}

/// <summary>
/// 前回までのプレイヤーのステータスを取得
/// </summary>
void DataSave::getLastTimeStatus() {
	//前回までの各コインを代入
	for (unsigned int i = 0; i != PlayerState::coin.size(); ++i)
		PlayerState::coin[i] = lastTimeStatus[i];
	//前回までの属性耐久値を代入
	for (unsigned int i = 0; i != PlayerState::attributeAccumulation.size(); ++i)
		PlayerState::attributeAccumulation[i] = lastTimeStatus[i + PlayerState::coin.size()];
	//前回までの戦闘スタイルを代入
	PlayerState::battleStyle = lastTimeStatus[PlayerState::coin.size() + PlayerState::attributeAccumulation.size()];
	//各マップ座標
	MapDraw::mapX = lastTimeStatus[9]; //前回までのマップx座標を代入
	MapDraw::mapY = lastTimeStatus[10]; //前回までのマップy座標を代入
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
}

/// <summary>
/// セーブデータの読み込み
/// </summary>
void DataSave::roadSaveData() {
	/* ステータス */
	roadBinaryFile(currentStatus, lastTimeStatus, statusData);
	getLastTimeStatus();
}

/// <summary>
/// 更新処理
/// </summary>
void DataSave::update() {
	/*DrawFormatString(0, 700, GetColor(255, 0, 0), "%d, %d, %d, %d",
	                 player.coin[0], player.coin[1], player.coin[2], player.coin[3], false);*/
}
