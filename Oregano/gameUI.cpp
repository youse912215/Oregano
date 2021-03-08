#include "gameUI.h"
#include "DxLib.h"
#include "constant.h"
#include "playerState.h"
#include "dataText.h"

DataText text_;
PlayerState state__;

GameUI::GameUI(Input& input, Player& player, MapDraw& map) :
	input(input), player(player), map(map), margin(16),
	/*�@���j���[ */
	menuLength(256, 64),
	menuSize(WIN_WIDTH - menuLength.x - margin, margin),
	/* �p�b�V�u */
	passiveSize(margin, WIN_HEIGHT - 128 - margin),
	/* ��Ԉُ� */
	conditionSize(WIN_WIDTH - 256 - margin, WIN_HEIGHT - 128 - margin),
	/* ���[�h */
	modeLeftSize(BLOCK_SIZE * 7 - margin, WIN_HEIGHT - 128 - margin),
	modeLength(64, 128),
	modeRightSize(BLOCK_SIZE * 16 + 32 - margin, WIN_HEIGHT - modeLength.y - margin),
	/* �A�N�V���� */
	actionLength(512, 128),
	actionSize(BLOCK_SIZE * 8 + 16 - margin, WIN_HEIGHT - actionLength.y - margin) {

	changeFlag = false;
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
/// �`�揈��
/// </summary>
void GameUI::draw() {
	drawBlur(); //�ڂ���

	DrawGraph(margin, margin, coinGraph, true); //�R�C��

	DrawRectGraph(menuSize.x, menuSize.y,
	              0, 0, menuLength.x, menuLength.y,
	              menuGraph, true, false, false); //���j���[

	DrawGraph(passiveSize.x, passiveSize.y, passiveGraph, true); //�p�b�V�u

	DrawGraph(conditionSize.x, conditionSize.y, conditionGraph, true); //��Ԉُ�

	DrawRectGraph(modeLeftSize.x, modeLeftSize.y,
	              0, 0, modeLength.x, modeLength.y, modeGraph,
	              true, false, false); //L���[�h

	DrawRectGraph(modeRightSize.x, modeRightSize.y,
	              modeLength.x, 0, modeLength.x, modeLength.y, modeGraph,
	              true, false, false); //R���[�h

	DrawRectGraph(actionSize.x, actionSize.y,
	              0, 0, actionLength.x, actionLength.y, actionGraph,
	              true, false, false); //�A�N�V����

	drawFilter();
}

void GameUI::update() {
	draw();
	text_.drawText();
}
