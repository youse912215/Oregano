#include "playerSlash.h"
#include "constant.h"
#include "DxLib.h"

PlayerSlash::PlayerSlash() : slashPos(0.0) {
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
void PlayerSlash::slashCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& slash) {
	if (cooldownFlag[SLASH]) cooldown[SLASH]++; //�N�[���_�E���J�n

	if (cooldown[SLASH] >= 20 && cooldown[SLASH] < 60) {
		slash = false; //�n�����߂�
	}
		//�N�[���_�E����60�b
	else if (cooldown[SLASH] >= 60) {
		cooldown[SLASH] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[SLASH] = false; //�N�[���_�E���t���O��false
	}
}

void PlayerSlash::draw(DataSource& source) {
	DrawGraph(static_cast<int>(slashPos.dx), static_cast<int>(slashPos.dy), source.slashGraph, true);
}
