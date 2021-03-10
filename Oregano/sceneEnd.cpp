#include "sceneEnd.h"
#include "sceneGame.h"
#include "sceneLoad.h"

SceneEnd::SceneEnd(Input& input) :
	input(input), startSize(128, 128), startPos(550, 700), maxTime(10000),
	changeTime(30), interval(0), endFlag(false) {
}

/// <summary>
/// 更新処理
/// </summary>
void SceneEnd::update() {
	//エンドシーンのとき
	if (SceneLoad::gameScene == END_SCENE) {
		SceneGame::countInterval(&interval, maxTime); //間隔時間をカウント

		//Aボタンを押したときかつ、intervalがchangeTime以上なら
		if (input.A && interval >= changeTime) {
			interval = 0; //間隔時間をリセット
			endFlag = true; //終了フラグをtrue
		}

		DrawGraph(0, 0, clear, true); //背景

		DrawRectGraph(startPos.x, startPos.y,
		              0, startSize.x * input.device,
		              startSize.x, startSize.y,
		              titleStart, true, false, false); //スタートボタン配置
	}
}
