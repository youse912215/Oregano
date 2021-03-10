#include "sceneGameOver.h"
#include "sceneLoad.h"

SceneGameOver::SceneGameOver(DataSave& data, Input& input) :
	data(data), input(input), charSize(128, 128), charPos(250, 575), charInterval(650),
	endFlag(false) {
}

void SceneGameOver::update() {
	//�Q�[���I�[�o�[�V�[���̂Ƃ�
	if (SceneLoad::gameScene == GAME_OVER_SCENE) {

		for (unsigned int i = 0; i != PlayerState::condition.size(); ++i) {
			PlayerState::condition[i] = false; //��Ԉُ��false
		}

		//R�{�^�����������Ƃ�
		if (input.RB) {
			endFlag = true; //�I���t���O��true
		}

		//L�{�^�����������Ƃ�
		if (input.LB) {
			data.loadSaveData(); //�O��̃Z�[�u�f�[�^��ǂݍ���
			SceneLoad::gameScene = GAME_SCENE; //�Q�[���V�[����
		}

		DrawGraph(0, 0, gameover, true); //�w�i

		DrawRectGraph(charPos.x, charPos.y,
		              0, charSize.y * input.device,
		              charSize.x, charSize.y, gameOverEnd,
		              true, false, false); //��������

		DrawRectGraph(charPos.x + charInterval, charPos.y,
		              charSize.x, charSize.y * input.device,
		              charSize.x, charSize.y, gameOverEnd,
		              true, false, false); //�E������
	}
}
