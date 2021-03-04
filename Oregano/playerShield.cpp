#include "playerShield.h"
#include "constant.h"
#include "DxLib.h"

PlayerShield::PlayerShield() : shieldQuantity(15), addQuantity(45), cooldownMax(120), shieldPos(0.0, 0.0), value(0) {
}

/// <summary>
/// シールドを追加で付与
/// </summary>
/// <param name="battleStyle">戦闘スタイル</param>
/// <returns></returns>
int PlayerShield::addShield(const int& battleStyle) {
	//戦闘スタイルが燕子花(対混乱)のとき
	if (battleStyle == CONFUSION) return addQuantity; //シールドを追加
	return 0;
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
void PlayerShield::countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& shield) {
	if (cooldownFlag[SHIELD] && !shield) cooldown[SHIELD]++; //クールダウン開始

	if (cooldown[SHIELD] >= cooldownMax) {
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

/// <summary>
/// 0以下は0にする処理
/// </summary>
void PlayerShield::zeroOut() {
	if (value <= 0) value = 0;
}

/// <summary>
/// シールドを付与
/// </summary>
/// <param name="battleStyle">戦闘スタイル</param>
void PlayerShield::giveShield(const int& battleStyle) {
	value = shieldQuantity + addShield(battleStyle); //シールド量を追加
}
