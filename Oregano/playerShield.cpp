#include "playerShield.h"
#include "constant.h"
#include "DxLib.h"

void PlayerShield::draw(DataSource& source) {
	DrawGraph(static_cast<int>(shieldPos.dx), static_cast<int>(shieldPos.dy), source.shieldGraph, true);
}

PlayerShield::PlayerShield() {
	shieldPos = 0; //�V�[���h�̍��W
	shieldValue = 15;
}


void PlayerShield::initialize(Vec2& pos) {
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
