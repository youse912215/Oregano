#include "dataSave.h"
#include "mapDraw.h"
#include "constant.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(Player& player, EventField& field)
	: player(player), field(field), currentStatus(STATUS_INFORMATION_SIZE),
	  currentPossession(PLAYER_ITEM_SIZE), currentCoin(COIN_INFORMATION_SIZE),
	  currentItem(ITEM_INFORMATION_SIZE) {
	statusData = "resource\\Data\\statusData.bin";
	coinData = "resource\\Data\\coinData.bin";
	itemData = "resource\\Data\\itemData.bin";
	possessionData = "resource\\Data\\possessionItemData.bin";
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

/// <summary>
/// 現在までのフィールドイベント状況を取得
/// </summary>
/// <param name="currentEvent">現在までのイベント</param>
/// <param name="fieldEvent">フィールドイベント</param>
void DataSave::getCurrentEvent(vector<int>& currentEvent, vector<int>& saveLocation) {
	for (unsigned int i = 0; i < currentEvent.size(); ++i)
		currentEvent[i] = saveLocation[i];
}

/// <summary>
/// 前回までのフィールドイベント状況を取得
/// </summary>
/// <param name="lastTimeEvent">前回までのイベント</param>
/// <param name="fieldEvent">フィールドイベント</param>
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
	/* 所持品 */
	getCurrentEvent(currentPossession, player.possessionItem);
	writeBinaryFile(currentPossession, lastTimePossession, possessionData);
	/* フィールドコイン */
	getCurrentEvent(currentCoin, field.coin);
	writeBinaryFile(currentCoin, lastTimeCoin, coinData);
	/* フィールドアイテム */
	getCurrentEvent(currentItem, field.item);
	writeBinaryFile(currentItem, lastTimeItem, itemData);
}

/// <summary>
/// セーブデータの読み込み
/// </summary>
void DataSave::roadSaveData() {
	/* ステータス */
	roadBinaryFile(currentStatus, lastTimeStatus, statusData);
	getLastTimeStatus();
	/* 所持品 */
	roadBinaryFile(currentPossession, lastTimePossession, possessionData);
	getLastTimeEvent(lastTimePossession, player.possessionItem);
	/* フィールドコイン */
	roadBinaryFile(currentCoin, lastTimeCoin, coinData);
	getLastTimeEvent(lastTimeCoin, field.coin);
	/* フィールドアイテム */
	roadBinaryFile(currentItem, lastTimeItem, itemData);
	getLastTimeEvent(lastTimeItem, field.item);
}

/// <summary>
/// 更新処理
/// </summary>
void DataSave::update() {
	DrawFormatString(0, 500, GetColor(120, 0, 100), "トレジャーランク:%d, 花萌葱:%d, 金糸雀:%d, 葡萄染:%d, 白百合:%d",
	                 player.status[TREASURE_RANK], player.status[GREEN_COIN], player.status[YELLOW_COIN],
	                 player.status[PURPLE_COIN], player.status[WHITE_COIN], false);
	DrawFormatString(0, 515, GetColor(120, 0, 100), "生命力:%d, 攻撃力:%d, 守備力:%d, 優先度:%d",
	                 player.status[LIFE], player.status[ATTACK],
	                 player.status[DEFENSE], player.status[PRIORITY], false);
	DrawFormatString(0, 530, GetColor(120, 0, 100), "猛毒耐性:%d, 猛毒属性値:%d, 麻痺耐性:%d, 麻痺属性値:%d",
	                 player.status[DEADLY_POISON_RESISTANCE], player.status[DEADLY_POISON_VALUE],
	                 player.status[PARALYSIS_RESISTANCE], player.status[PARALYSIS_VALUE], false);
	DrawFormatString(0, 545, GetColor(120, 0, 100), "催眠耐性:%d, 催眠属性値:%d, 出血耐性:%d, 出血属性値:%d",
	                 player.status[HYPNOSIS_RESISTANCE], player.status[HYPNOSIS_VALUE],
	                 player.status[BLOODING_RESISTANCE], player.status[BLOODING_VALUE], false);

	DrawFormatString(0, 630, GetColor(0, 0, 0), "非常食:%d, パン:%d, 牛肉:%d, 魚:%d、豆:%d, 鶏肉:%d, ボトル小:%d, ボトル大:%d",
	                 player.possessionItem[0], player.possessionItem[1], player.possessionItem[2],
	                 player.possessionItem[3], player.possessionItem[4], player.possessionItem[5],
	                 player.possessionItem[6], player.possessionItem[7], false);
	DrawFormatString(0, 645, GetColor(0, 0, 0),
	                 "不思議なボトル:%d, 毒草:%d, 解毒草:%d, 健康草:%d、チューリップ:%d, アロエ:%d, マリーゴールド:%d, 麻酔花:%d",
	                 player.possessionItem[8], player.possessionItem[9], player.possessionItem[10],
	                 player.possessionItem[11], player.possessionItem[12], player.possessionItem[13],
	                 player.possessionItem[14], player.possessionItem[15], false);
	DrawFormatString(0, 660, GetColor(0, 0, 0),
	                 "薔薇:%d, 寝袋:%d, スコップ:%d, ピッケル:%d、ナイフ:%d, 長靴:%d, アロマキノコ:%d, 止血剤:%d",
	                 player.possessionItem[16], player.possessionItem[17], player.possessionItem[18],
	                 player.possessionItem[19], player.possessionItem[20], player.possessionItem[21],
	                 player.possessionItem[22], player.possessionItem[23], false);
	DrawFormatString(0, 675, GetColor(0, 0, 0),
	                 "健康食:%d, 猛毒薬:%d, 麻酔薬:%d, 暗視草:%d、ルピナス:%d, タンポポ:%d, マッスルダケ:%d, 豊樹草:%d",
	                 player.possessionItem[24], player.possessionItem[25], player.possessionItem[26],
	                 player.possessionItem[27], player.possessionItem[28], player.possessionItem[29],
	                 player.possessionItem[30], player.possessionItem[31], false);
	DrawFormatString(0, 690, GetColor(0, 0, 0),
	                 "赤実:%d, バーナー:%d, 東国飯:%d, シーパワー:%d、ブラッドエキス:%d, ブラッドポーション:%d、快眠ダケ:%d, スリープジェル:%d",
	                 player.possessionItem[32], player.possessionItem[33], player.possessionItem[34],
	                 player.possessionItem[35], player.possessionItem[36], player.possessionItem[37],
	                 player.possessionItem[38], player.possessionItem[39], false);
}
