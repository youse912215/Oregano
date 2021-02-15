#include "dataSave.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(EventBase& event, Player& player) : position(event), player(player), statusData(14) {
	fileName = "resource\\Data\\saveData1.bin";
}

DataSave::~DataSave() {
}

/// <summary>
/// バイナリファイルの書き込み
/// </summary>
void DataSave::writeBinaryFile() {
	getCurrentStatus(); //ステータスを取得

	vecOut.clear(); //出力配列のクリア

	for (auto& i : statusData)
		vecOut.push_back(i); //ステータスを順番に格納

	int sizeOut = vecOut.size(); //ベクター配列のサイズ数を格納

	/* バイナリファイル書き込み */
	ofstream fileWrite(fileName, ios::binary);
	if (!fileWrite) return;

	fileWrite.write(reinterpret_cast<char*>(&vecOut[0]),
	                static_cast<std::streamsize>(sizeof(int)) * sizeOut);
	fileWrite.close(); //閉じる
}

/// <summary>
/// バイナリファイル読み込み
/// </summary>
void DataSave::roadBinaryFile() {
	/* バイナリファイル読み込み */
	ifstream fileRead(fileName, ios::binary);
	if (!fileRead) return;

	vector<char> binChar(getFileSize(fileName));
	if (!fileRead.read(&binChar[0], getFileSize(fileName))) return;
	fileRead.close(); //閉じる

	/* 16進数を10進数に変換し、出力配列に格納 */
	for (unsigned int i = 0; i < statusData.size(); ++i)
		vecOut.push_back((binChar[i * 4] & 0xff)
			+ static_cast<int>((binChar[i * 4 + 1] & 0xff) * pow(16, 2)));
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
/// プレイヤーのステータスを取得
/// </summary>
void DataSave::getCurrentStatus() {
	statusData[LIFE] = player.status[LIFE]; //生命力
	statusData[ATTACK] = player.status[ATTACK]; //攻撃力
	statusData[DEFENSE] = player.status[DEFENSE]; //守備力
	statusData[DEADLY_POISON_RESISTANCE] = player.status[DEADLY_POISON_RESISTANCE]; //猛毒耐性
	statusData[DEADLY_POISON_VALUE] = player.status[DEADLY_POISON_VALUE]; //猛毒属性値
	statusData[PARALYSIS_RESISTANCE] = player.status[PARALYSIS_RESISTANCE]; //麻痺耐性
	statusData[PARALYSIS_VALUE] = player.status[PARALYSIS_VALUE]; //麻痺属性値
	statusData[HYPNOSIS_RESISTANCE] = player.status[HYPNOSIS_RESISTANCE]; //催眠耐性
	statusData[HYPNOSIS_VALUE] = player.status[HYPNOSIS_VALUE]; //催眠属性値
	statusData[PRIORITY] = player.status[PRIORITY]; //優先度
	statusData[CURRENT_MAP_X] = position.currentMapPosition(MAP_X); //現在のマップx座標
	statusData[CURRENT_MAP_Y] = position.currentMapPosition(MAP_Y); //現在のマップy座標
	statusData[CENTRAL_POSITION_X] = position.centralPlayerPosition(MAP_X); //プレイヤーの中央x座標
	statusData[CENTRAL_POSITION_Y] = position.centralPlayerPosition(MAP_Y); //プレイヤーの中央y座標
}

/// <summary>
/// 更新処理
/// </summary>
void DataSave::update() {
	roadBinaryFile(); //バイナリファイル読み込み

	DrawFormatString(0, 500, GetColor(0, 0, 0), "%d, %d, %d, %d",
	                 vecOut[CURRENT_MAP_X], vecOut[CURRENT_MAP_Y],
	                 vecOut[CENTRAL_POSITION_X], vecOut[CENTRAL_POSITION_Y],
	                 false);
}
