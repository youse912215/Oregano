#include "sceneTitle.h"
#include "sceneLoad.h"
#include "DxLib.h"

SceneTitle::SceneTitle(Input& input) :
	input(input), deviceSize(512, 128), startSize(128, 128), startPos(550, 575) {
}

void SceneTitle::update() {
	//タイトルシーンのとき
	if (SceneLoad::gameScene == TITLE_SCENE) {

		input.deviceModeChange(); //キーボードとジョイパッドを切り替える

		//Aボタンを押したとき
		if (input.A)
			SceneLoad::gameScene = ROAD_SCENE; //ロードシーンへ

		DrawGraph(0, 0, source.title, true); //背景

		DrawRectGraph(0, WIN_HEIGHT - deviceSize.y,
		              0, deviceSize.y * input.device,
		              deviceSize.x, deviceSize.y,
		              source.deviceChange1, true, false, false); //デバイス種類

		DrawRectGraph(startPos.x, startPos.y,
		              0, startSize.x * input.device,
		              startSize.x, startSize.y,
		              source.titleStart, true, false, false); //スタートボタン配置
	}
}
