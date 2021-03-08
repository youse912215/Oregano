#include "sceneRoad.h"
#include "constant.h"
#include "mapAutogeneration.h"
#include "dataSource.h"
#include "dataText.h"

MapAutogeneration autogeneration;
MapLoad load;
DataSource source;
DataText text;

int SceneRoad::gameScene = TITLE_SCENE;

SceneRoad::SceneRoad(DataSave& save) : save(save) {
}

SceneRoad::~SceneRoad() {
}

/// <summary>
/// 更新処理
/// </summary>
void SceneRoad::update() {
	if (gameScene == ROAD_SCENE) {
		save.roadMapData(); //マップデータの読み込み
		save.roadSaveData(); //セーブデータ読み込み
		autogeneration.writeRandomMap(); //マップ自動生成
		load.roadMapData(); //マップデータ読み込み
		text.roadFont(); //フォントのロード

		gameScene = GAME_SCENE; //ゲームシーンへ
	}
}

/// <summary>
/// タイトル画面でロードしたマップ三次元配列を返す
/// </summary>
vector<vector<vector<int>>>& SceneRoad::roadingMap() {
	return load.mapAll;
}
