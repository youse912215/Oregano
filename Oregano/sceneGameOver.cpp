#include "sceneGameOver.h"
#include "sceneLoad.h"

SceneGameOver::SceneGameOver(DataSave& data, Input& input, SceneGame& game) :
	data(data), input(input), game(game), charSize(128, 128), charPos(250, 575), charInterval(650),
	endFlag(false) {
}

void SceneGameOver::update() {
	//ゲームオーバーシーンのとき
	if (SceneLoad::gameScene == GAME_OVER_SCENE) {

		//Rボタンを押したとき
		if (input.RB) {
			endFlag = true; //終了フラグをtrue
		}

		//Lボタンを押したとき
		if (input.LB) {
			for (unsigned int i = 0; i != PlayerState::condition.size(); ++i) {
				PlayerState::condition[i] = false; //状態異常をfalse
				PlayerState::attributeAccumulation[i] = 0; //耐久値をリセット
			}

			game.gameTime = 0; //ゲーム時間をリセット
			game.enemyFlag = false; //敵フラグをfalse

			data.loadSaveData(); //前回のセーブデータを読み込み
			SceneLoad::gameScene = GAME_SCENE; //ゲームシーンへ
		}

		DrawGraph(0, 0, source.gameover, true); //背景

		DrawRectGraph(charPos.x, charPos.y,
		              0, charSize.y * input.device,
		              charSize.x, charSize.y, source.gameOverEnd,
		              true, false, false); //左側文字

		DrawRectGraph(charPos.x + charInterval, charPos.y,
		              charSize.x, charSize.y * input.device,
		              charSize.x, charSize.y, source.gameOverEnd,
		              true, false, false); //右側文字
	}
}
