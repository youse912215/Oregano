#include "sceneLoad.h"
#include "constant.h"
#include "mapAutogeneration.h"
#include "dataSource.h"
#include "dataText.h"

MapAutogeneration autogeneration;
MapLoad load;
DataSource source;
DataText text;

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
		save.initLoadSaveData(); //セーブデータ読み込み
		autogeneration.writeRandomMap(); //マップ自動生成
		load.loadMapData(); //マップデータ読み込み
		autogeneration.resetFile(); //CSVファイルのリセット
		text.loadFont(); //フォントのロード

		gameScene = GAME_SCENE; //ゲームシーンへ
	}
}

/// <summary>
/// タイトル画面でロードしたマップ三次元配列を返す
/// </summary>
vector<vector<vector<int>>>& SceneLoad::roadingMap() {
	return load.mapAll;
}
