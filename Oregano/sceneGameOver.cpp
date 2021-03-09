#include "sceneGameOver.h"
#include "sceneLoad.h"

SceneGameOver::SceneGameOver(DataSave& data, Input& input) :
	data(data), input(input), endFlag(false) {
}

void SceneGameOver::update() {
	//ゲームオーバーシーンのとき
	if (SceneLoad::gameScene == GAME_OVER_SCENE) {

		for (unsigned int i = 0; i != PlayerState::condition.size(); ++i) {
			PlayerState::condition[i] = false; //状態異常をfalse
		}

		//Lボタンを押したとき
		if (input.LB) {
			endFlag = true; //終了フラグをtrue
		}

		//Rボタンを押したとき
		if (input.RB) {
			data.loadSaveData(); //前回のセーブデータを読み込み
			SceneLoad::gameScene = GAME_SCENE; //ゲームシーンへ
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), "gameover", false);
	}
}
