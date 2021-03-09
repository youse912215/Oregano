#include "gameUI.h"
#include "DxLib.h"
#include "constant.h"
#include "playerState.h"
#include "dataText.h"
#include "sceneLoad.h"

DataText text_;
PlayerState state__;

GameUI::GameUI(Input& input, Player& player, MapDraw& map) :
	input(input), player(player), map(map), margin(16), eventSize(9), eventLength(4),
	/*�@���j���[ */
	menuLength(256, 64), menuSize(WIN_WIDTH - menuLength.x - margin, margin),
	/* �p�b�V�u */
	passiveLength(256, 128), passiveSize(margin, WIN_HEIGHT - 128 - margin),
	/* ��Ԉُ� */
	conditionSize(WIN_WIDTH - 256 - margin, WIN_HEIGHT - 128 - margin),
	/* �A�N�V���� */
	actionLength(512, 128), actionSize(BLOCK_SIZE * 8 + 16 - margin, WIN_HEIGHT - actionLength.y - margin),
	/* �����o�� */
	speechBalloonLength(64, 64), speechBalloonPos(HALF_WIN_WIDTH - 32, HALF_WIN_HEIGHT - 100),
	/* �}�b�v��C�x���g */
	mapEventPos(MAP_EVENT_SIZE), eventNum(0) {
}

GameUI::~GameUI() {
}

/// <summary>
/// �ڂ����̕`��
/// </summary>
void GameUI::drawBlur() {
	//�}�b�v���W�i3, 2�j���E��ȊO�͒ʏ�ڂ���
	if (!(map.currentMap.x >= 3 && map.currentMap.y <= 2))
		DrawGraph(0, 0, blurGraph1, true);
		//����Ɏ��E�����߂�ڂ���
	else
		DrawGraph(0, 0, blurGraph2, true);
}

/// <summary>
/// �t�B���^�[�`��
/// </summary>
void GameUI::drawFilter() {
	/* ���݂̐퓬�X�^�C���ȊO�̃p�b�V�uUI���t�B���^�[�ŉB�� */
	for (int i = 0; i <= BLOODING; ++i) {
		if (PlayerState::battleStyle != i)
			DrawGraph(passiveSize.x + BLOCK_SIZE * i,
			          passiveSize.y + BLOCK_SIZE, filterGraph1, true);
	}
	/* ���݂̏�Ԉُ�ȊO���t�B���^�[�ŉB�� */
	for (int i = 0; i <= BLOODING; ++i) {
		if (!PlayerState::condition[i])
			DrawGraph(conditionSize.x + BLOCK_SIZE * i, conditionSize.y + BLOCK_SIZE,
			          filterGraph1, true);
	}
	/* ���ݏo���Ȃ��A�N�V�������t�B���^�[�ŉB�� */
	for (int i = 0; i < 3; ++i) {
		if (player.actionFlag[i])
			DrawGraph(actionSize.x + BLOCK_SIZE * 2 * i, actionSize.y, filterGraph2, true);
	}
	if (!state__.anyCondition())
		DrawGraph(actionSize.x + BLOCK_SIZE * 6, actionSize.y, filterGraph2, true);
}

/// <summary>
/// �v���C���[�ƃC�x���g�ʒu�̈�v����
/// </summary>
/// <param name="i">�C�x���g�ԍ�</param>
bool GameUI::positionMatchDecision(const int& i) {
	return map.currentMap.x == mapEventPos[i * eventLength] //�}�b�vx���W
		&& map.currentMap.y == mapEventPos[i * eventLength + 1] //�}�b�vy���W
		&& abs(map.blockArea.x - mapEventPos[i * eventLength + 2]) <= 1 //���x���W
		&& abs(map.blockArea.y - mapEventPos[i * eventLength + 3]) <= 1; //���y���W
}

/// <summary>
/// �C�x���g�p�����o���̕`��
/// </summary>
void GameUI::drawSpeechBalloon() {
	//�C�x���g�����J��Ԃ�
	for (int i = 0; i < eventSize; ++i) {
		//�v���C���[�ƃC�x���g�ʒu����v
		if (!positionMatchDecision(i))
			continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
		DrawRectGraph(speechBalloonPos.x, speechBalloonPos.y,
		              speechBalloonLength.x * input.device, 0,
		              speechBalloonLength.x, speechBalloonLength.y, source.eventGraph,
		              true, false, false); //�����o��

		eventNum = i; //������ʒu�̃C�x���g�ԍ�����

		if (input.VIEW) {
			//�ړI�n�_�̃C�x���g�ԍ�(eventSize - 1)�ȊO�Ȃ�
			if (eventNum != eventSize - 1) {
				SceneLoad::gameScene = SAVE_SCENE; //VIEW�{�^�����������Ƃ��A�Z�[�u�V�[����
			}
			else SceneLoad::gameScene = END_SCENE; //VIEW�{�^�����������Ƃ��A�G���h�V�[����
		}
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void GameUI::draw() {
	DrawGraph(margin, margin, coinGraph, true); //�R�C��

	DrawRectGraph(menuSize.x, menuSize.y,
	              0, menuLength.y * input.device,
	              menuLength.x, menuLength.y, menuGraph,
	              true, false, false); //���j���[

	DrawRectGraph(passiveSize.x, passiveSize.y,
	              0, passiveLength.y * input.device,
	              passiveLength.x, passiveLength.y, passiveGraph,
	              true, false, false); //�p�b�V�u

	DrawGraph(conditionSize.x, conditionSize.y, conditionGraph, true); //��Ԉُ�

	DrawRectGraph(actionSize.x, actionSize.y,
	              0, actionLength.y * input.device,
	              actionLength.x, actionLength.y, actionGraph,
	              true, false, false); //�A�N�V����
	drawFilter(); //�t�B���^�[�`��
}

void GameUI::update() {
	drawBlur(); //�ڂ���
	draw();
	text_.drawText();
	drawSpeechBalloon(); //�C�x���g�p�����o���`��
}
