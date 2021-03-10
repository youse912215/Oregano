#include "sceneMenu.h"
#include "sceneLoad.h"
#include "sceneGame.h"

SceneMenu::SceneMenu(Input& input) :
	input(input), devicePos(300, WIN_HEIGHT / 2),
	deviceSize(1024, 256), maxTime(10000), changeTime(30), interval(0) {
}

void SceneMenu::update() {
	//メニューシーンのとき
	if (SceneLoad::gameScene == MENU_SCENE) {
		SceneGame::countInterval(&interval, maxTime); //間隔時間をカウント

		input.deviceModeChange(); //キーボードとジョイパッドを切り替える

		//メニューボタンを押したときかつ、intervalがchangeTime以上なら
		if (input.MENU && interval >= changeTime) {

			interval = 0; //間隔時間をリセット
			SceneLoad::gameScene = GAME_SCENE; //ゲームシーンへ
		}

		DrawGraph(0, 0, source.menu, true); //背景

		DrawRectGraph(devicePos.x, devicePos.y,
		              0, deviceSize.y * input.device,
		              deviceSize.x, deviceSize.y, source.deviceChange2,
		              true, false, false); //デバイス種類
	}
}
