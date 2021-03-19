#include "sceneLoad.h"
#include "constant.h"
#include "mapAutogeneration.h"
#include "dataSource.h"

MapAutoGeneration autogeneration; //マップ自動生成クラス
MapLoad load; //ロードクラス
DataSource source; //データソースクラス

int SceneLoad::gameScene = TITLE_SCENE; //タイトルシーン

SceneLoad::SceneLoad(DataSave& save) : save(save) {
}

SceneLoad::~SceneLoad() {
}

/// <summary>
/// 更新処理
/// </summary>
void SceneLoad::update() {
	if (gameScene == ROAD_SCENE) {
		save.loadMapData(); //マップデータの読み込み

		save.loadInitSaveData(); //セーブデータ読み込み

		autogeneration.writeRandomMap(); //マップ自動生成

		load.loadMapData(); //マップデータ読み込み

		autogeneration.resetFile(); //CSVファイルのリセット

		gameScene = GAME_SCENE; //ゲームシーンへ
	}
}

/// <summary>
/// タイトル画面でロードしたマップ三次元配列を返す
/// </summary>
vector<vector<vector<int>>>& SceneLoad::roadingMap() {
	return load.mapAll;
}
