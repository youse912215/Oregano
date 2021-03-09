#include "sceneTitle.h"
#include "sceneLoad.h"
#include "DxLib.h"

SceneTitle::SceneTitle(Input& input) :
	input(input) {
}

void SceneTitle::update() {
	//タイトルシーンのとき
	if (SceneLoad::gameScene == TITLE_SCENE) {

		input.deviceModeChange(); //キーボードとジョイパッドを切り替える

		//Aボタンを押したとき
		if (input.A)
			SceneLoad::gameScene = ROAD_SCENE; //ロードシーンへ

		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", input.device);
	}
}
