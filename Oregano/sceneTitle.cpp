#include "sceneTitle.h"
#include "constant.h"
#include "mapAutogeneration.h"
#include "DxLib.h"

MapAutogeneration autogeneration;
MapLoad load;

SceneTitle::SceneTitle(DataSave& save) : save(save) {
}

SceneTitle::~SceneTitle() {
}

void SceneTitle::titleProcess() {
	CALL_ONCE(save.roadSaveData()); //ファイル読み込み処理
	CALL_ONCE(autogeneration.writeRandomMap()); //マップ自動生成
	load.roadMapData();

	EventBase::gameScene = GAME_SCENE;
}

/// <summary>
/// タイトル画面でロードしたマップ三次元配列を返す
/// </summary>
vector<vector<vector<int>>>& SceneTitle::returnMapAll() {
	return load.mapAll;
}
