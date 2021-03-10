#include "sceneSave.h"
#include "sceneLoad.h"
#include "sceneGame.h"
#include "dataSave.h"

SceneSave::SceneSave(DataSave& data, Input& input, GameUI& UI) :
	data(data), input(input), UI(UI), maxTime(10000), changeTime(40), interval(0) {
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

		if (UI.eventNum == 0) {
			DrawGraph(0, 0, event1, true);
		}
		else if (UI.eventNum == 1) {
			DrawGraph(0, 0, event2, true);
		}
		else {
			DrawGraph(0, 0, event3, true);
		}
	}
}
