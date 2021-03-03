#include "playerSlash.h"
#include "constant.h"
#include "DxLib.h"

PlayerSlash::PlayerSlash() : slashPos(0.0) {
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">プレイヤーの座標</param>
void PlayerSlash::initialize(Vec2d& pos) {
	slashPos = pos - HALF_BLOCK_SIZE_D; //刃座標
}

/// <summary>
/// 刃のクールダウン処理
/// </summary>
void PlayerSlash::slashCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& slash) {
	if (cooldownFlag[SLASH]) cooldown[SLASH]++; //クールダウン開始

	if (cooldown[SLASH] >= 20 && cooldown[SLASH] < 60) {
		slash = false; //刃を収める
	}
		//クールダウンは60秒
	else if (cooldown[SLASH] >= 60) {
		cooldown[SLASH] = 0; //クールダウンをリセット
		cooldownFlag[SLASH] = false; //クールダウンフラグをfalse
	}
}

void PlayerSlash::draw(DataSource& source) {
	DrawGraph(static_cast<int>(slashPos.dx), static_cast<int>(slashPos.dy), source.slashGraph, true);
}
