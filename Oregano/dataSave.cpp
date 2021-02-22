#include "dataSave.h"
#include "mapDraw.h"
#include "constant.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(Player& player, EventField& field)
	: player(player), field(field),
	  currentStatus(STATUS_INFORMATION_SIZE), //ステータス
	  /* 所持品 */
	  currentPossessionItem(PLAYER_ITEM_SIZE), currentPossessionAccessory(PLAYER_ACCESSORY_SIZE),
	  currentPossessionJewel(PLAYER_JEWEL_SIZE), currentPossessionMineral(PLAYER_MINERAL_SIZE),
	  /* フィールド */
	  currentCoin(COIN_INFORMATION_SIZE), currentItem(ITEM_INFORMATION_SIZE),
	  currentAccessory(ACCESSORY_INFORMATION_SIZE), currentJewel(JEWEL_INFORMATION_SIZE),
	  currentMineral(MINERAL_INFORMATION_SIZE) {
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
}

/// <summary>
/// 更新処理
/// </summary>
void DataSave::update() {
	DrawFormatString(0, 500, GetColor(120, 0, 100), "トレジャーランク:%d, 花萌葱:%d, 金糸雀:%d, 葡萄染:%d, 白百合:%d",
	                 player.status[TREASURE_RANK], player.status[GREEN_COIN], player.status[YELLOW_COIN],
	                 player.status[PURPLE_COIN], player.status[WHITE_COIN], false);
	DrawFormatString(0, 515, GetColor(120, 0, 100), "現在生命力:%d, 最大生命力:%d, 攻撃力:%d, 交渉力:%d",
	                 player.status[CURRENT_LIFE], player.status[MAX_LIFE],
	                 player.status[ATTACK], player.status[BARGAINING_POWER], false);
	DrawFormatString(0, 530, GetColor(120, 0, 100), "猛毒耐性:%d, 猛毒属性値:%d, 猛毒蓄積:%d,  麻痺耐性:%d, 麻痺属性値:%d, 麻痺蓄積:%d",
	                 player.status[DEADLY_POISON_RESISTANCE], player.status[DEADLY_POISON_VALUE],
	                 player.status[DEADLY_POISON_ACCUMULATION],
	                 player.status[PARALYSIS_RESISTANCE], player.status[PARALYSIS_VALUE],
	                 player.status[PARALYSIS_ACCUMULATION], false);
	DrawFormatString(0, 545, GetColor(120, 0, 100), "催眠耐性:%d, 催眠属性値:%d, 催眠蓄積:%d, 出血耐性:%d, 出血属性値:%d, 出血蓄積:%d",
	                 player.status[HYPNOSIS_RESISTANCE], player.status[HYPNOSIS_VALUE],
	                 player.status[HYPNOSIS_ACCUMULATION],
	                 player.status[BLOODING_RESISTANCE], player.status[BLOODING_VALUE],
	                 player.status[BLOODING_ACCUMULATION], false);

	DrawFormatString(0, 630, GetColor(0, 0, 0), "非常食:%d, パン:%d, 肉:%d, 魚:%d、豆:%d, 地図:%d, ボトル小:%d, ボトル大:%d",
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

	DrawFormatString(0, 720, GetColor(0, 0, 0), "Bネック:%d, Bチョー:%d, Bペンダ:%d, Bリング:%d、Bピアス:%d, テレサ:%d, マチルダ:%d, ナガタラ:%d",
	                 player.possessionAccessory[0], player.possessionAccessory[1], player.possessionAccessory[2],
	                 player.possessionAccessory[3], player.possessionAccessory[4], player.possessionAccessory[5],
	                 player.possessionAccessory[6], player.possessionAccessory[7], false);
	DrawFormatString(0, 735, GetColor(0, 0, 0), "Sネック:%d, Sチョー:%d, Sペンダ:%d, Sリング:%d、Sピアス:%d, 東国紋章:%d, Gネック:%d, Gペンダ:%d",
	                 player.possessionAccessory[8], player.possessionAccessory[9], player.possessionAccessory[10],
	                 player.possessionAccessory[11], player.possessionAccessory[12], player.possessionAccessory[14],
	                 player.possessionAccessory[15], player.possessionAccessory[16], false);

	DrawFormatString(0, 770, GetColor(0, 0, 0), "エメラルド:%d, Tガーネット:%d, Cトルマリン:%d, ペリD:%d、花萌葱ロードN:%d",
	                 player.possessionJewel[0], player.possessionJewel[1], player.possessionJewel[2],
	                 player.possessionJewel[3], player.possessionJewel[20], false);

	DrawFormatString(0, 800, GetColor(0, 0, 0), "軽石:%d, 東栄石:%d, 南栄石:%d, 西栄石:%d、北栄石:%d, 黄金超石:%d",
	                 player.possessionMineral[0], player.possessionMineral[1], player.possessionMineral[2],
	                 player.possessionMineral[3], player.possessionMineral[4], player.possessionMineral[4], false);
}
