#include "mapAutogeneration.h"
#include "random.h"
#include <algorithm>
#include <fstream>
#include <sstream>

MapAutogeneration::MapAutogeneration() :
	roadMap(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
	copyMap(TOTAL_MAPS_X * TOTAL_MAPS_Y, vector<vector<int>>(AREA_HEIGHT, vector<int>(AREA_WIDTH))) {
}

MapAutogeneration::~MapAutogeneration() {
}

/// <summary>
/// マップの自動生成
/// </summary>
/// <param name="random">ランダム関数の値</param>
/// <param name="randomMapNum">ランダムマップ名（番号）</param>
/// <returns></returns>
int MapAutogeneration::autogenerationMap(const int& random, const int& randomMapNum) {
	/* ランダムマップ1 */
	if (randomMapNum == RANDOM_MAP1) {
		if (random < 25) return FLOOR_NORMAL;
		return WALL;
	}
	/* ランダムマップ2 */
	if (randomMapNum == RANDOM_MAP2) {
		if (random < 25) return FLOOR_NORMAL;
		if (random % 2 == 0) return POISON;
		return WALL;
	}
	return FLOOR_NORMAL; //以外のとき通常床を返す
}

/// <summary>
/// ランダムマップの数字をランダムに割り当て
/// </summary>
/// <param name="randomMapNum"></param>
void MapAutogeneration::AssigningRandomNum(const int& randomMapNum) {
	vector<int>::iterator itr;
	int index = 0;
	bool loop = false;
	while (!loop) {
		for (unsigned int i = 0; i != roadMap.size();) {

			itr = find(roadMap[i].begin(), roadMap[i].end(), randomMapNum); //対象のイテレーターを見つける

			if (itr != roadMap[i].end()) {
				index = distance(roadMap[i].begin(), itr); //ランダムマップのインデックスを入手
				roadMap[i][index] = autogenerationMap(getRandom(0, 30), randomMapNum); //マップの自動生成
			}
			else {
				++i; //加算
			}
		}
		loop = true; //whileを抜ける
	}
}

/// <summary>
/// csvファイルの書き込み
/// </summary>
/// <param name="x">マップのx座標</param>
/// <param name="y">マップのy座標</param>
void MapAutogeneration::writeFile(const int& x, const int& y, vector<vector<int>>& map) {
	ofstream fileWrite(mapConfirmation(x, y, initialCsv));
	if (!fileWrite) return;

	for (unsigned int j = 0; j != map.at(0).size(); ++j) {
		for (unsigned int i = 0; i != map.size(); ++i) {
			fileWrite << map[j][i] << ","; //vector配列の中を順に格納
		}
		fileWrite << endl; //改行
	}

	fileWrite.close(); //閉じる
}

/// <summary>
/// ランダムマップのファイル書き込み
/// </summary>
void MapAutogeneration::writeRandomMap() {

	for (unsigned int y = 0; y < TOTAL_MAPS_Y; ++y) {
		for (unsigned int x = 0; x < TOTAL_MAPS_X; ++x) {
			fileImport(x, y, roadMap); //マップデータのファイル読み込み

			saveInitMap(x, y); //最初のマップをコピー（一時保存）

			AssigningRandomNum(RANDOM_MAP1); //ランダムマップ1の数字をランダムに割り当て
			AssigningRandomNum(RANDOM_MAP2); //ランダムマップ2の数字をランダムに割り当て

			writeFile(x, y, roadMap); //csvファイルの書き込み
		}
	}
}

/// <summary>
/// 最初のマップをコピー（一時保存）
/// </summary>
/// <param name="x">マップのx座標</param>
/// <param name="y">マップのy座標</param>
void MapAutogeneration::saveInitMap(const int& x, const int& y) {
	copyMap[x + y * TOTAL_MAPS_Y].clear(); //中身を一旦クリア

	for (auto& i : roadMap) //読み込んだ2次元配列データを
		copyMap[x + y * TOTAL_MAPS_Y].push_back(i); //末尾に値を挿入する
}

/// <summary>
/// CSVファイルを最初の状態にリセット
/// </summary>
void MapAutogeneration::resetFile() {
	for (unsigned int y = 0; y < TOTAL_MAPS_Y; ++y) {
		for (unsigned int x = 0; x < TOTAL_MAPS_X; ++x) {
			writeFile(x, y, copyMap[x + y * TOTAL_MAPS_Y]);
		}
	}
}
