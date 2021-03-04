#include "playerKnife.h"

#include <DxLib.h>

PlayerKnife::PlayerKnife() :
	curvatureSpeed(KNIFE_SPEED / 2.0), maxRange(BLOCK_SIZE * 3.0),
	knifePos(0.0, 0.0), knifeAddPos(0.0, 0.0) {
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">プレイヤーの座標</param>
/// <param name="knifeCenter">プレイヤーの中心座標</param>
void PlayerKnife::initialize(Vec2d& pos, Vec2d& knifeCenter) {
	knifePos = pos + knifeAddPos; //ナイフの座標の更新
	knifeCenter = HALF_BLOCK_SIZE_D + knifePos; //ナイフの中心位置の更新
}

/// <summary>
/// ナイフのクールダウン処理
/// </summary>
/// <param name="cooldown">クールダウン</param>
/// <param name="cooldownFlag">クールダウンフラグ</param>
void PlayerKnife::countCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag) {
	if (cooldownFlag[KNIFE]) cooldown[KNIFE]++; //クールダウン開始

	//クールダウンは30秒
	if (cooldown[KNIFE] >= 30) {
		cooldown[KNIFE] = 0; //クールダウンをリセット
		cooldownFlag[KNIFE] = false; //クールダウンフラグをfalse
	}
}

/// <summary>
/// ナイフのポジジョンをセットする
/// </summary>
void PlayerKnife::setKnifePosition(Vec2d& pos) {
	/* x方向 */
	if (knifePos.dx < pos.dx) knifeAddPos.dx -= KNIFE_SPEED;
	else if (knifePos.dx > pos.dx) knifeAddPos.dx += KNIFE_SPEED;
	else knifeAddPos.dx = 0.0;
	/* y方向 */
	if (knifePos.dy < pos.dy) knifeAddPos.dy -= KNIFE_SPEED;
	else if (knifePos.dy > pos.dy)knifeAddPos.dy += KNIFE_SPEED;
	else knifeAddPos.dy = 0.0;
}

/// <summary>
/// ナイフのポジジョンをリセットする
/// </summary>
void PlayerKnife::resetKnifePosition(Vec2d& center, bool& knife) {
	if (deleteKnife(center)) {
		knife = false;
		knifeAddPos = 0.0;
	}
}

/// <summary>
/// ナイフの加速（ジョイパッドだと曲げることも可能）
/// スティック方向に対して、曲げる速度を加算
/// </summary>
void PlayerKnife::accelKnife(Input& input) {
	/* x方向 */
	if (input.STICK[LEFT]) knifeAddPos.dx -= curvatureSpeed;
	else if (input.STICK[RIGHT]) knifeAddPos.dx += curvatureSpeed;
	/* y方向 */
	if (input.STICK[UP]) knifeAddPos.dy -= curvatureSpeed;
	else if (input.STICK[DOWN]) knifeAddPos.dy += curvatureSpeed;
}

/// <summary>
/// ナイフの削除条件
/// </summary>
/// <returns></returns>
bool PlayerKnife::deleteKnife(Vec2d& center) {
	//プレイヤーからの距離が3マス分離れているか
	return abs(knifePos.dx + HALF_BLOCK_SIZE_D - center.dx) >= maxRange
		|| abs(knifePos.dy + HALF_BLOCK_SIZE_D - center.dy) >= maxRange;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="source">データソース</param>
void PlayerKnife::draw(DataSource& source) {
	DrawGraph(static_cast<int>(knifePos.dx), static_cast<int>(knifePos.dy), source.knifeGraph, true);
}
