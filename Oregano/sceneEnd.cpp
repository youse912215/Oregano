#include "sceneEnd.h"
#include "sceneGame.h"
#include "sceneLoad.h"

SceneEnd::SceneEnd(Input& input) :
	input(input), maxTime(10000), changeTime(30), interval(0), endFlag(false) {
}

/// <summary>
/// 更新処理
/// </summary>
void SceneEnd::update() {
	//エンドシーンのとき
	if (SceneLoad::gameScene == END_SCENE) {
		SceneGame::countInterval(&interval, maxTime); //間隔時間をカウント

		//VIEWボタンを押したときかつ、intervalがchangeTime以上なら
		if (input.VIEW && interval >= changeTime) {

			interval = 0; //間隔時間をリセット
			endFlag = true; //終了フラグをtrue
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "clear", false);
	}
}
