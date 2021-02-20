#include "dataSave.h"
#include "mapDraw.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(EventBase& event, Player& player) : position(event), player(player), statusData(15) {
	saveDataFile = "resource\\Data\\saveData1.bin";
}

DataSave::~DataSave() {
}

/// <summary>
/// ファイルサイズを取得
/// </summary>
/// <param name="fName">ファイルの名前</param>
int DataSave::getFileSize(string fName) {
	ifstream fileRoad(fName, ifstream::ate);
	size_t fileSize = static_cast<size_t>(fileRoad.tellg());
	return fileSize;
}

/// <summary>
/// バイナリファイルの書き込み
/// </summary>
void DataSave::writeBinaryFile() {
	lastTimeData.clear(); //出力配列のクリア

	for (auto& i : statusData)
		lastTimeData.push_back(i); //ステータスを順番に格納

	int sizeOut = lastTimeData.size(); //ベクター配列のサイズ数を格納

	/* バイナリファイル書き込み */
	ofstream fileWrite(saveDataFile, ios::binary);
	if (!fileWrite) return;

	fileWrite.write(reinterpret_cast<char*>(&lastTimeData[0]),
	                static_cast<std::streamsize>(sizeof(int)) * sizeOut);
	fileWrite.close(); //閉じる
}

/// <summary>
/// バイナリファイルの読み込み
/// </summary>
void DataSave::roadBinaryFile() {
	/* バイナリファイル読み込み */
	ifstream fileRead(saveDataFile, ios::binary);
	if (!fileRead) return;

	vector<char> binChar(getFileSize(saveDataFile));
	if (!fileRead.read(&binChar[0], getFileSize(saveDataFile))) return;
	fileRead.close(); //閉じる

	/* 16進数を10進数に変換し、出力配列に格納 */
	for (unsigned int i = 0; i < statusData.size(); ++i)
		lastTimeData.push_back((binChar[i * 4] & 0xff)
			+ static_cast<int>((binChar[i * 4 + 1] & 0xff) * pow(16, 2)));
}

/// <summary>
/// 現在までのプレイヤーのステータスを取得
/// </summary>
void DataSave::getCurrentStatus() {
	for (unsigned int i = 0; i <= PRIORITY; ++i)
		statusData[i] = player.status[i];
	statusData[CURRENT_MAP_X] = MapDraw::mapX; //現在のマップx座標を代入
	statusData[CURRENT_MAP_Y] = MapDraw::mapY; //現在のマップy座標を代入
}

/// <summary>
/// 前回までのプレイヤーのステータスを取得
/// </summary>
void DataSave::getLastTimeStatus() {
	for (unsigned int i = 0; i <= PRIORITY; ++i)
		player.status[i] = lastTimeData[i];
	MapDraw::mapX = lastTimeData[CURRENT_MAP_X]; //前回までのマップx座標を代入
	MapDraw::mapY = lastTimeData[CURRENT_MAP_Y]; //前回までのマップy座標を代入
}

/// <summary>
/// セーブデータの書き込み
/// </summary>
void DataSave::writeSaveData() {
	getCurrentStatus(); //現在までのステータスを取得
	writeBinaryFile(); //バイナリファイルの書き込み
}

/// <summary>
/// セーブデータの読み込み
/// </summary>
void DataSave::roadSaveData() {
	roadBinaryFile(); //バイナリファイルの読み込み
	getLastTimeStatus(); //前回までのステータスを取得
}

/// <summary>
/// 更新処理
/// </summary>
void DataSave::update() {
	DrawFormatString(0, 500, GetColor(0, 0, 0), "%d, %d",
	                 lastTimeData[CURRENT_MAP_X], lastTimeData[CURRENT_MAP_Y], false);
}
