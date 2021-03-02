#include "playerShield.h"
#include "constant.h"
#include "DxLib.h"

void PlayerShield::draw(DataSource& source) {
	DrawGraph(static_cast<int>(shieldPos.dx), static_cast<int>(shieldPos.dy), source.shieldGraph, true);
}

PlayerShield::PlayerShield() {
	shieldPos = 0; //シールドの座標
	shieldValue = 15;
}


void PlayerShield::initialize(Vec2& pos) {
	shieldPos = pos;
}

/// <summary>
/// シールドのクールダウン処理
/// </summary>
void PlayerShield::shieldCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& shield) {
	if (cooldownFlag[SHIELD] && !shield) cooldown[SHIELD]++; //クールダウン開始

	if (cooldown[SHIELD] >= 120) {
		cooldown[SHIELD] = 0; //クールダウンをリセット
		cooldownFlag[SHIELD] = false; //クールダウンフラグをfalse
	}
}
