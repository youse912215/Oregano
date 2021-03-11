#include "sceneGameOver.h"
#include "sceneLoad.h"

SceneGameOver::SceneGameOver(DataSave& data, Input& input, SceneGame& game) :
	data(data), input(input), game(game), charSize(128, 128), charPos(250, 575), charInterval(650),
	maxTime(40), interval(0), pushFlag(false), endFlag(false) {
}

/// <summary>
/// �Ԋu���Ԃ��J�E���g
/// </summary>
void SceneGameOver::countInterval() {
	//�Ԋu���Ԃ��ő厞�Ԉȉ��Ȃ�
	if (interval <= maxTime)
		interval++; //���Ԃ��J�E���g
	else
		pushFlag = true; //�v�b�V���t���O��true
}

/// <summary>
/// �l�̃��Z�b�g
/// </summary>
void SceneGameOver::resetValue() {
	for (unsigned int i = 0; i != PlayerState::condition.size(); ++i) {
		PlayerState::condition[i] = false; //��Ԉُ��false
	}

	game.gameTime = 0; //�Q�[�����Ԃ����Z�b�g
	game.enemyFlag = false; //�G�t���O��false

	pushFlag = false; //�v�b�V���t���O��false
	interval = 0; //�Ԋu���Ԃ����Z�b�g
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneGameOver::draw() {
	DrawGraph(0, 0, source.gameover, true); //�w�i

	DrawRectGraph(charPos.x, charPos.y,
	              0, charSize.y * input.device,
	              charSize.x, charSize.y, source.gameOverEnd,
	              true, false, false); //��������

	DrawRectGraph(charPos.x + charInterval, charPos.y,
	              charSize.x, charSize.y * input.device,
	              charSize.x, charSize.y, source.gameOverEnd,
	              true, false, false); //�E������
}

void SceneGameOver::update() {
	//�Q�[���I�[�o�[�V�[���̂Ƃ�
	if (SceneLoad::gameScene == GAME_OVER_SCENE) {

		countInterval(); //�Ԋu���Ԃ��J�E���g

		//R�{�^�����������Ƃ����A�v�b�V���t���O��true�̂Ƃ�
		if (input.RB && pushFlag) {
			endFlag = true; //�I���t���O��true
		}

		//L�{�^�����������Ƃ����A�v�b�V���t���O��true�̂Ƃ�
		if (input.LB && pushFlag) {
			resetValue(); //�l�̃��Z�b�g

			data.loadSaveData(); //�O��̃Z�[�u�f�[�^��ǂݍ���
			SceneLoad::gameScene = GAME_SCENE; //�Q�[���V�[����
		}

		draw(); //�`�揈��
	}
}
