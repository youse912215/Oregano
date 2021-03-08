#include "sceneSave.h"
#include "sceneRoad.h"
#include "dataSave.h"

SceneSave::SceneSave(DataSave& data, Input& input) : data(data), input(input) {
}

void SceneSave::update() {
	if (SceneRoad::gameScene == SAVE_SCENE) {
		if (input.VIEW) {
			data.writeSaveData();
			SceneRoad::gameScene = GAME_SCENE;
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "save", false);
	}
}
