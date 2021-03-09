#include "sceneTitle.h"
#include "sceneLoad.h"

SceneTitle::SceneTitle(Input& input) :
	input(input) {
}

void SceneTitle::update() {
	//タイトルシーンのとき
	if (SceneLoad::gameScene == TITLE_SCENE) {
		//Aボタンを押したとき
		if (input.A)
			SceneLoad::gameScene = ROAD_SCENE; //ロードシーンへ
	}
}
