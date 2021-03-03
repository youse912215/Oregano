#include "playerShield.h"
#include "constant.h"
#include "DxLib.h"


PlayerShield::PlayerShield() : shieldPos(0.0, 0.0), shieldValue(15) {
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">プレイヤーの座標</param>
void PlayerShield::initialize(Vec2d& pos) {
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

/// <summary>
/// 描画処理
/// </summary>
/// <param name="source">データソース</param>
void PlayerShield::draw(DataSource& source) {
	DrawGraph(static_cast<int>(shieldPos.dx), static_cast<int>(shieldPos.dy), source.shieldGraph, true);
}
