#include "sceneSave.h"
#include "sceneLoad.h"
#include "sceneGame.h"
#include "dataSave.h"

SceneSave::SceneSave(DataSave& data, Input& input) :
	data(data), input(input), maxTime(10000), changeTime(40), interval(0) {
}

/// <summary>
/// �X�V����
/// </summary>
void SceneSave::update() {
	if (SceneLoad::gameScene == SAVE_SCENE) {
		SceneGame::countInterval(&interval, maxTime); //�Ԋu���Ԃ��J�E���g

		//VIEW�{�^�����������Ƃ����Ainterval��changeTime�ȏ�Ȃ�
		if (input.VIEW && interval >= changeTime) {

			interval = 0; //�Ԋu���Ԃ����Z�b�g
			data.writeSaveData(); //�f�[�^���Z�[�u����
			SceneLoad::gameScene = GAME_SCENE; //�Q�[���V�[���֖߂�
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "save", false);
	}
}
