#include "dataSave.h"
#include "mapDraw.h"
#include "constant.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(Player& player, EventField& field)
	: player(player), field(field), currentStatus(STATUS_SIZE + 2), currentCoin(COIN_INFORMATION_QUANTITY) {
	statusData = "resource\\Data\\statusData.bin";
	coinData = "resource\\Data\\coinData.bin";
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

	vector<char> binChar(getFileSize(fileName));
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
	for (unsigned int i = 0; i <= PRIORITY; ++i)
		currentStatus[i] = player.status[i];
	currentStatus[CURRENT_MAP_X] = MapDraw::mapX; //現在のマップx座標を代入
	currentStatus[CURRENT_MAP_Y] = MapDraw::mapY; //現在のマップy座標を代入
}

/// <summary>
/// 前回までのプレイヤーのステータスを取得
/// </summary>
void DataSave::getLastTimeStatus() {
	for (unsigned int i = 0; i <= PRIORITY; ++i)
		player.status[i] = lastTimeStatus[i];
	MapDraw::mapX = lastTimeStatus[CURRENT_MAP_X]; //前回までのマップx座標を代入
	MapDraw::mapY = lastTimeStatus[CURRENT_MAP_Y]; //前回までのマップy座標を代入
}

void DataSave::getCurrentCoin() {
	for (unsigned int i = 0; i < currentCoin.size(); ++i)
		currentCoin[i] = field.coin[i]; //現在までのコイン状況を取得
}

void DataSave::getLastTimeCoin() {
	for (unsigned int i = 0; i < currentCoin.size(); ++i)
		field.coin[i] = lastTimeCoin[i]; //前回までのコイン状況を取得
}

/// <summary>
/// セーブデータの書き込み
/// </summary>
void DataSave::writeSaveData() {
	getCurrentStatus();
	writeBinaryFile(currentStatus, lastTimeStatus, statusData);

	getCurrentCoin();
	writeBinaryFile(currentCoin, lastTimeCoin, coinData);
}

/// <summary>
/// セーブデータの読み込み
/// </summary>
void DataSave::roadSaveData() {
	/* ステータス */
	roadBinaryFile(currentStatus, lastTimeStatus, statusData);
	getLastTimeStatus();

	/* フィールドコイン */
	roadBinaryFile(currentCoin, lastTimeCoin, coinData);
	getLastTimeCoin();
}

/// <summary>
/// 更新処理
/// </summary>
void DataSave::update() {
	DrawFormatString(0, 500, GetColor(0, 0, 0), "花萌葱:%d, 金糸雀:%d, 葡萄染:%d, 白百合:%d",
	                 player.status[GREEN_COIN], player.status[YELLOW_COIN],
	                 player.status[PURPLE_COIN], player.status[WHITE_COIN], false);

	DrawFormatString(0, 515, GetColor(0, 0, 0), "生命力:%d, 攻撃力:%d, 守備力:%d, 優先度:%d",
	                 player.status[LIFE], player.status[ATTACK],
	                 player.status[DEFENSE], player.status[PRIORITY], false);

	DrawFormatString(0, 530, GetColor(0, 0, 0),
	                 "mx:%d, my:%d, cx:%d, cy:%d, dir:%d, type:%d, rank:%d, TofF:%d",
	                 field.coin[0], field.coin[1], field.coin[2], field.coin[3],
	                 field.coin[4], field.coin[5], field.coin[6], field.coin[7], false);
	DrawFormatString(0, 545, GetColor(0, 0, 0),
	                 "mx:%d, my:%d, cx:%d, cy:%d, dir:%d, type:%d, rank:%d, TofF:%d",
	                 field.coin[8], field.coin[9], field.coin[10], field.coin[11],
	                 field.coin[12], field.coin[13], field.coin[14], field.coin[15], false);
}
