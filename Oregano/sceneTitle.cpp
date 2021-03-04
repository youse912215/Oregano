#include "sceneTitle.h"
#include "constant.h"
#include "mapAutogeneration.h"
#include "dataSource.h"

MapAutogeneration autogeneration;
MapLoad load;
DataSource source;

SceneTitle::SceneTitle(DataSave& save) : save(save) {
}

SceneTitle::~SceneTitle() {
}

/// <summary>
/// 更新処理
/// </summary>
void SceneTitle::update() {
	CALL_ONCE(save.roadSaveData()); //ファイル読み込み処理
	CALL_ONCE(autogeneration.writeRandomMap()); //マップ自動生成
	load.roadMapData(); //マップデータ読み込み

	EventBase::gameScene = GAME_SCENE; //ゲームシーンへ
}

/// <summary>
/// タイトル画面でロードしたマップ三次元配列を返す
/// </summary>
vector<vector<vector<int>>>& SceneTitle::roadingMap() {
	return load.mapAll;
}
