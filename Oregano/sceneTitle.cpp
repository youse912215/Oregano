#include "sceneTitle.h"
#include "sceneLoad.h"
#include "DxLib.h"

SceneTitle::SceneTitle(Input& input) :
	input(input), deviceSize(512, 128), startSize(128, 128), startPos(550, 575) {
}

void SceneTitle::update() {
	//�^�C�g���V�[���̂Ƃ�
	if (SceneLoad::gameScene == TITLE_SCENE) {

		input.deviceModeChange(); //�L�[�{�[�h�ƃW���C�p�b�h��؂�ւ���

		//A�{�^�����������Ƃ�
		if (input.A)
			SceneLoad::gameScene = ROAD_SCENE; //���[�h�V�[����

		DrawGraph(0, 0, source.title, true); //�w�i

		DrawRectGraph(0, WIN_HEIGHT - deviceSize.y,
		              0, deviceSize.y * input.device,
		              deviceSize.x, deviceSize.y,
		              source.deviceChange1, true, false, false); //�f�o�C�X���

		DrawRectGraph(startPos.x, startPos.y,
		              0, startSize.x * input.device,
		              startSize.x, startSize.y,
		              source.titleStart, true, false, false); //�X�^�[�g�{�^���z�u
	}
}
