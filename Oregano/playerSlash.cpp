#include "playerSlash.h"
#include "constant.h"
#include "DxLib.h"

PlayerSlash::PlayerSlash() : drawTime(0), graphNum(3), graphWidth(128), popTime(20), cooldownMax(60),
                             slashPos(0.0) {
}

/// <summary>
/// �`�掞�ԃJ�E���g
/// </summary>
/// <param name="slash">�n�t���O</param>
void PlayerSlash::countTime() {
	drawTime = drawTime <= graphNum ? ++drawTime : 0; //graphNum�����Ԃ��J�E���g
}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">�v���C���[�̍��W</param>
void PlayerSlash::initialize(Vec2d& pos) {
	slashPos = pos - HALF_BLOCK_SIZE_D; //�n���W
}

/// <summary>
/// �n�̃N�[���_�E������
/// </summary>
/// <param name="cooldown">�N�[���_�E��</param>
/// <param name="cooldownFlag">�N�[���_�E���t���O</param>
/// <param name="actionFlag">�n�t���O</param>
void PlayerSlash::countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag,
                                std::vector<bool>& actionFlag) {
	if (cooldownFlag[SLASH]) cooldown[SLASH]++; //�N�[���_�E���J�n

	if (cooldown[SLASH] >= popTime && cooldown[SLASH] < cooldownMax) {
		actionFlag[SLASH] = false; //�n�����߂�
	}
		//�N�[���_�E����60�b
	else if (cooldown[SLASH] >= cooldownMax) {
		cooldown[SLASH] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[SLASH] = false; //�N�[���_�E���t���O��false
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="source">�f�[�^�\�[�X�N���X</param>
void PlayerSlash::draw(DataSource& source) {
	DrawRectGraph(static_cast<int>(slashPos.dx), static_cast<int>(slashPos.dy),
	              graphWidth * drawTime, 0, graphWidth, graphWidth,
	              source.slashGraph, true, false); //�n����]���ĕ`��
}
