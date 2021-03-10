#include "sceneMenu.h"
#include "sceneLoad.h"
#include "sceneGame.h"

SceneMenu::SceneMenu(Input& input) :
	input(input), devicePos(300, WIN_HEIGHT / 2),
	deviceSize(1024, 256), maxTime(10000), changeTime(30), interval(0) {
}

void SceneMenu::update() {
	//���j���[�V�[���̂Ƃ�
	if (SceneLoad::gameScene == MENU_SCENE) {
		SceneGame::countInterval(&interval, maxTime); //�Ԋu���Ԃ��J�E���g

		input.deviceModeChange(); //�L�[�{�[�h�ƃW���C�p�b�h��؂�ւ���

		//���j���[�{�^�����������Ƃ����Ainterval��changeTime�ȏ�Ȃ�
		if (input.MENU && interval >= changeTime) {

			interval = 0; //�Ԋu���Ԃ����Z�b�g
			SceneLoad::gameScene = GAME_SCENE; //�Q�[���V�[����
		}

		DrawGraph(0, 0, source.menu, true); //�w�i

		DrawRectGraph(devicePos.x, devicePos.y,
		              0, deviceSize.y * input.device,
		              deviceSize.x, deviceSize.y, source.deviceChange2,
		              true, false, false); //�f�o�C�X���
	}
}
