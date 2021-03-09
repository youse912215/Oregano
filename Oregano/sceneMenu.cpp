#include "sceneMenu.h"
#include "sceneLoad.h"
#include "sceneGame.h"

SceneMenu::SceneMenu(Input& input) : input(input), maxTime(10000), changeTime(30), interval(0) {
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

		DrawFormatString(0, 0, GetColor(255, 255, 255), "menu", false);
	}
}
