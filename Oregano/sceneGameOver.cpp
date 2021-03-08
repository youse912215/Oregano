#include "sceneGameOver.h"
#include "SceneRoad.h"

SceneGameOver::SceneGameOver(DataSave& data, Input& input) :
	data(data), input(input), endFlag(false) {
}

void SceneGameOver::update() {
	//ゲームオーバーシーンのとき
	if (SceneRoad::gameScene == GAME_OVER_SCENE) {
		//Lボタンを押したとき
		if (input.LB) {
			endFlag = true; //終了フラグをtrue
		}

		//Rボタンを押したとき
		if (input.RB) {
			data.roadSaveData(); //前回のセーブデータを読み込み
			SceneRoad::gameScene = GAME_SCENE; //ゲームシーンへ
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), "gameover", false);
	}
}
