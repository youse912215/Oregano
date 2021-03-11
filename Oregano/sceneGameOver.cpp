#include "sceneGameOver.h"
#include "sceneLoad.h"

SceneGameOver::SceneGameOver(DataSave& data, Input& input, SceneGame& game) :
	data(data), input(input), game(game), charSize(128, 128), charPos(250, 575), charInterval(650),
	maxTime(40), interval(0), pushFlag(false), endFlag(false) {
}

/// <summary>
/// 間隔時間をカウント
/// </summary>
void SceneGameOver::countInterval() {
	//間隔時間が最大時間以下なら
	if (interval <= maxTime)
		interval++; //時間をカウント
	else
		pushFlag = true; //プッシュフラグをtrue
}

/// <summary>
/// 値のリセット
/// </summary>
void SceneGameOver::resetValue() {
	for (unsigned int i = 0; i != PlayerState::condition.size(); ++i) {
		PlayerState::condition[i] = false; //状態異常をfalse
	}

	game.gameTime = 0; //ゲーム時間をリセット
	game.enemyFlag = false; //敵フラグをfalse

	pushFlag = false; //プッシュフラグをfalse
	interval = 0; //間隔時間をリセット
}

/// <summary>
/// 描画処理
/// </summary>
void SceneGameOver::draw() {
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

void SceneGameOver::update() {
	//ゲームオーバーシーンのとき
	if (SceneLoad::gameScene == GAME_OVER_SCENE) {

		countInterval(); //間隔時間をカウント

		//Rボタンを押したときかつ、プッシュフラグがtrueのとき
		if (input.RB && pushFlag) {
			endFlag = true; //終了フラグをtrue
		}

		//Lボタンを押したときかつ、プッシュフラグがtrueのとき
		if (input.LB && pushFlag) {
			resetValue(); //値のリセット

			data.loadSaveData(); //前回のセーブデータを読み込み
			SceneLoad::gameScene = GAME_SCENE; //ゲームシーンへ
		}

		draw(); //描画処理
	}
}
