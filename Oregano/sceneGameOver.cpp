#include "sceneGameOver.h"
#include "sceneLoad.h"

SceneGameOver::SceneGameOver(DataSave& data, Input& input) :
	data(data), input(input), endFlag(false) {
}

void SceneGameOver::update() {
	//�Q�[���I�[�o�[�V�[���̂Ƃ�
	if (SceneLoad::gameScene == GAME_OVER_SCENE) {

		for (unsigned int i = 0; i != PlayerState::condition.size(); ++i) {
			PlayerState::condition[i] = false; //��Ԉُ��false
		}

		//L�{�^�����������Ƃ�
		if (input.LB) {
			endFlag = true; //�I���t���O��true
		}

		//R�{�^�����������Ƃ�
		if (input.RB) {
			data.loadSaveData(); //�O��̃Z�[�u�f�[�^��ǂݍ���
			SceneLoad::gameScene = GAME_SCENE; //�Q�[���V�[����
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), "gameover", false);
	}
}
