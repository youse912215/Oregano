#include "sceneMenu.h"
#include "SceneRoad.h"

SceneMenu::SceneMenu(Input& input) : input(input) {
}

void SceneMenu::update() {
	//メニューシーンのとき
	if (SceneRoad::gameScene == MENU_SCENE) {
		if (input.MENU) SceneRoad::gameScene = GAME_SCENE; //ゲームシーンへ
		DrawFormatString(0, 0, GetColor(255, 255, 255), "menu", false);
	}
}
