#include "playerShield.h"
#include "constant.h"
#include "DxLib.h"


PlayerShield::PlayerShield() : shieldPos(0.0, 0.0), shieldValue(15) {
}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">�v���C���[�̍��W</param>
void PlayerShield::initialize(Vec2d& pos) {
	shieldPos = pos;
}

/// <summary>
/// �V�[���h�̃N�[���_�E������
/// </summary>
void PlayerShield::shieldCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& shield) {
	if (cooldownFlag[SHIELD] && !shield) cooldown[SHIELD]++; //�N�[���_�E���J�n

	if (cooldown[SHIELD] >= 120) {
		cooldown[SHIELD] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[SHIELD] = false; //�N�[���_�E���t���O��false
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="source">�f�[�^�\�[�X</param>
void PlayerShield::draw(DataSource& source) {
	DrawGraph(static_cast<int>(shieldPos.dx), static_cast<int>(shieldPos.dy), source.shieldGraph, true);
}
