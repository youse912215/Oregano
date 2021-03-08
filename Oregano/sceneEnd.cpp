#include "sceneEnd.h"

#include "SceneRoad.h"

SceneEnd::SceneEnd(Input& input) : input(input), endFlag(false) {
}

/// <summary>
/// 更新処理
/// </summary>
void SceneEnd::update() {
	//エンドシーンのとき
	if (SceneRoad::gameScene == END_SCENE) {
		//VIEWボタンを押したとき
		if (input.VIEW) {
			endFlag = true; //終了フラグをtrue
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "clear", false);
	}
}
