#include "sceneGameOver.h"
#include "SceneRoad.h"

SceneGameOver::SceneGameOver(DataSave& data, Input& input) :
	data(data), input(input), endFlag(false) {
}

void SceneGameOver::update() {
	//�Q�[���I�[�o�[�V�[���̂Ƃ�
	if (SceneRoad::gameScene == GAME_OVER_SCENE) {
		//L�{�^�����������Ƃ�
		if (input.LB) {
			endFlag = true; //�I���t���O��true
		}

		//R�{�^�����������Ƃ�
		if (input.RB) {
			data.roadSaveData(); //�O��̃Z�[�u�f�[�^��ǂݍ���
			SceneRoad::gameScene = GAME_SCENE; //�Q�[���V�[����
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), "gameover", false);
	}
}
