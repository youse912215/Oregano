#include "sceneEnd.h"
#include "sceneGame.h"
#include "sceneLoad.h"

SceneEnd::SceneEnd(Input& input) :
	input(input), maxTime(10000), changeTime(30), interval(0), endFlag(false) {
}

/// <summary>
/// �X�V����
/// </summary>
void SceneEnd::update() {
	//�G���h�V�[���̂Ƃ�
	if (SceneLoad::gameScene == END_SCENE) {
		SceneGame::countInterval(&interval, maxTime); //�Ԋu���Ԃ��J�E���g

		//VIEW�{�^�����������Ƃ����Ainterval��changeTime�ȏ�Ȃ�
		if (input.VIEW && interval >= changeTime) {

			interval = 0; //�Ԋu���Ԃ����Z�b�g
			endFlag = true; //�I���t���O��true
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "clear", false);
	}
}
