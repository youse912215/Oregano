#include "sceneEnd.h"
#include "sceneGame.h"
#include "sceneLoad.h"

SceneEnd::SceneEnd(Input& input) :
	input(input), startSize(128, 128), startPos(550, 700), maxTime(10000),
	changeTime(30), interval(0), endFlag(false) {
}

/// <summary>
/// �X�V����
/// </summary>
void SceneEnd::update() {
	//�G���h�V�[���̂Ƃ�
	if (SceneLoad::gameScene == END_SCENE) {
		SceneGame::countInterval(&interval, maxTime); //�Ԋu���Ԃ��J�E���g

		//A�{�^�����������Ƃ����Ainterval��changeTime�ȏ�Ȃ�
		if (input.A && interval >= changeTime) {
			interval = 0; //�Ԋu���Ԃ����Z�b�g
			endFlag = true; //�I���t���O��true
		}

		DrawGraph(0, 0, clear, true); //�w�i

		DrawRectGraph(startPos.x, startPos.y,
		              0, startSize.x * input.device,
		              startSize.x, startSize.y,
		              titleStart, true, false, false); //�X�^�[�g�{�^���z�u
	}
}
