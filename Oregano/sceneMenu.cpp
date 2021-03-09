#include "sceneMenu.h"
#include "sceneLoad.h"
#include "sceneGame.h"

SceneMenu::SceneMenu(Input& input) : input(input), maxTime(10000), changeTime(30), interval(0) {
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

		DrawFormatString(0, 0, GetColor(255, 255, 255), "menu", false);
	}
}
