#include "sceneTitle.h"
#include "sceneLoad.h"
#include "DxLib.h"

SceneTitle::SceneTitle(Input& input) :
	input(input) {
}

void SceneTitle::update() {
	//�^�C�g���V�[���̂Ƃ�
	if (SceneLoad::gameScene == TITLE_SCENE) {

		input.deviceModeChange(); //�L�[�{�[�h�ƃW���C�p�b�h��؂�ւ���

		//A�{�^�����������Ƃ�
		if (input.A)
			SceneLoad::gameScene = ROAD_SCENE; //���[�h�V�[����

		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", input.device);
	}
}
