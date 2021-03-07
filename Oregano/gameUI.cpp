#include "gameUI.h"
#include "DxLib.h"
#include "constant.h"

GameUI::GameUI(Input& input, MapDraw& map) :
	input(input), map(map), margin(16),
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
		DrawGraph(0, 0, source.blurGraph1, true);
		//����Ɏ��E�����߂�ڂ���
	else
		DrawGraph(0, 0, source.blurGraph2, true);
}

/// <summary>
/// �`�揈��
/// </summary>
void GameUI::draw() {
	drawBlur(); //�ڂ���

	DrawGraph(margin, margin, source.coinGraph, true); //�R�C��

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
}

void GameUI::update() {
	draw();
}
