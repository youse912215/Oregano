#include "sceneSave.h"
#include "sceneLoad.h"
#include "sceneGame.h"
#include "dataSave.h"

SceneSave::SceneSave(DataSave& data, Input& input) :
	data(data), input(input), maxTime(10000), changeTime(40), interval(0) {
}

/// <summary>
/// 更新処理
/// </summary>
void SceneSave::update() {
	if (SceneLoad::gameScene == SAVE_SCENE) {
		SceneGame::countInterval(&interval, maxTime); //間隔時間をカウント

		//VIEWボタンを押したときかつ、intervalがchangeTime以上なら
		if (input.VIEW && interval >= changeTime) {

			interval = 0; //間隔時間をリセット
			data.writeSaveData(); //データをセーブする
			SceneLoad::gameScene = GAME_SCENE; //ゲームシーンへ戻る
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "save", false);
	}
}
