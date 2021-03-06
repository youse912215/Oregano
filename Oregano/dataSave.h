#pragma once
#include "playerState.h"
#include "gameUI.h"
#include <vector>
#include <string>

using namespace std;

class DataSave {
private:
	PlayerState& player; //プレイヤー状態クラス
	GameUI& UI; //UIクラス

	vector<int> currentStatus; //現在までのステータス格納用
	vector<int> lastTimeStatus; //前回までのステータス格納用

	vector<int> roadMap; //マップバッファ確保用
	vector<int> storeMap; //マップ格納用

	string statusData; //セーブデータのバイナリファイル
	string mapData; //セーブデータのバイナリファイル
	string initStatusData; //初期のセーブデータのバイナリファイル

	int getFileSize(string fileName); //ファイルサイズを取得

	void writeBinaryFile(vector<int>& currentData, vector<int>& lastTimeData,
	                     string fileName); //バイナリファイルのの書き込み
	void loadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData,
	                    string fileName); //バイナリファイルの読み込み

	void getCurrentStatus(); //現在までのプレイヤーのステータスを取得
	void getLastTimeStatus(); //前回までのプレイヤーのステータスを取得

	void storingEvent(vector<int>& roadData, vector<int>& saveLocation); //イベント座標を格納

public:
	DataSave(PlayerState& player, GameUI& UI);
	~DataSave();

	void writeSaveData(); //セーブデータの書き込み
	void loadSaveData(); //セーブデータの読み込み
	void loadInitSaveData(); //初期セーブデータの読み込み

	void loadMapData(); //マップデータの読み込み
};
