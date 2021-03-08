#include "sceneTitle.h"
#include "constant.h"
#include "mapAutogeneration.h"
#include "dataSource.h"
#include "dataText.h"

MapAutogeneration autogeneration;
MapLoad load;
DataSource source;
DataText text;

int SceneTitle::gameScene = TITLE_SCENE;

SceneTitle::SceneTitle(DataSave& save) : save(save) {
}

SceneTitle::~SceneTitle() {
}

/// <summary>
/// 更新処理
/// </summary>
void SceneTitle::update() {
	save.roadMapData(); //マップデータの読み込み
	save.roadSaveData(); //セーブデータ読み込み
	autogeneration.writeRandomMap(); //マップ自動生成
	load.roadMapData(); //マップデータ読み込み
	text.roadFont(); //フォントのロード

	gameScene = GAME_SCENE; //ゲームシーンへ
}

/// <summary>
/// タイトル画面でロードしたマップ三次元配列を返す
/// </summary>
vector<vector<vector<int>>>& SceneTitle::roadingMap() {
	return load.mapAll;
}
