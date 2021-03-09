#include "sceneTitle.h"
#include "sceneLoad.h"

SceneTitle::SceneTitle(Input& input) :
	input(input) {
}

void SceneTitle::update() {
	//�^�C�g���V�[���̂Ƃ�
	if (SceneLoad::gameScene == TITLE_SCENE) {
		//A�{�^�����������Ƃ�
		if (input.A)
			SceneLoad::gameScene = ROAD_SCENE; //���[�h�V�[����
	}
}
