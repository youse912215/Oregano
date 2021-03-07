#include "playerSlash.h"
#include "constant.h"
#include "DxLib.h"

PlayerSlash::PlayerSlash() : drawTime(0), graphNum(3), graphWidth(128), slashPos(0.0) {
}

/// <summary>
/// 描画時間カウント
/// </summary>
/// <param name="slash">刃フラグ</param>
void PlayerSlash::countTime() {
	drawTime = drawTime <= graphNum ? ++drawTime : 0; //graphNum分時間をカウント
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
/// <param name="cooldown">クールダウン</param>
/// <param name="cooldownFlag">クールダウンフラグ</param>
/// <param name="slash">刃フラグ</param>
void PlayerSlash::countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& slash) {
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

/// <summary>
/// 描画処理
/// </summary>
/// <param name="source">データソースクラス</param>
void PlayerSlash::draw(DataSource& source) {
	DrawRectGraph(static_cast<int>(slashPos.dx), static_cast<int>(slashPos.dy),
	              graphWidth * drawTime, 0, graphWidth, graphWidth,
	              source.slashGraph, true, false); //刃を回転して描画
}
