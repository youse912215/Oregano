#include "enemyTracking.h"

EnemyTracking::EnemyTracking() :
	distance(0.0, 0.0), distanceSquared(0.0, 0.0), distanceNormalized(0.0, 0.0), moveSpeed(0.0, 0.0),
	magnification(3), onLineDistance(20) {
}

/// <summary>
/// 移動速度を取得
/// </summary>
void EnemyTracking::getMoveSpeed(Player& player, Vec2d& pos) {
	distance = player.center - (QUARTER_BLOCK_SIZE_D + pos); //距離
	distanceSquared = distance * distance; //距離の2乗
	distanceNormalized.dx = abs(distance.dx) / sqrt(distanceSquared.dx + distanceSquared.dy); //x方向の正規化
	distanceNormalized.dy = abs(distance.dy) / sqrt(distanceSquared.dx + distanceSquared.dy); //y方向の正規化
	moveSpeed = 4 * distanceNormalized; //移動速度
}

/// <summary>
/// 画面上のx座標にいる条件
/// </summary>
bool EnemyTracking::onScreenX(Vec2d& screenPos) {
	return screenPos.dx >= 0 && screenPos.dx <= WIN_WIDTH;
}

/// <summary>
/// 画面上のy座標にいる条件
/// </summary>
bool EnemyTracking::onScreenY(Vec2d& screenPos) {
	return screenPos.dy >= 0 && screenPos.dy <= WIN_HEIGHT;
}

/// <summary>
/// 直線上の移動(x方向)
/// </summary>
/// <param name="player">プレイヤークラス</param>
/// <param name="screenPos">スクリーン座標</param>
/// <returns></returns>
int EnemyTracking::moveOnLineX(Player& player, Vec2d& screenPos) {
	//プレイヤーの直線上付近(x距離がonLineDistance以下)にいるとき
	if (abs(screenPos.dx - player.center.dx) <= onLineDistance)
		return magnification; //magnification倍にする
	return 1; //等倍
}

/// <summary>
/// 直線上の移動(y方向)
/// </summary>
/// <param name="player">プレイヤークラス</param>
/// <param name="screenPos">スクリーン座標</param>
/// <returns></returns>
int EnemyTracking::moveOnLineY(Player& player, Vec2d& screenPos) {
	//プレイヤーの直線上付近(y距離がonLineDistance以下)にいるとき
	if (abs(screenPos.dy - player.center.dy) <= onLineDistance)
		return magnification; //magnification倍にする
	return 1; //等倍
}

/// <summary>
/// 移動処理
/// プレイヤーの左か右かで移動方向が変化する
/// </summary>
void EnemyTracking::move(Player& player, Vec2d& pos, Vec2d& screenPos) {
	/* x方向の移動 */
	if (screenPos.dx >= 0
		&& screenPos.dx < player.center.dx
		&& onScreenY(screenPos)) {
		pos.dx += moveSpeed.dx * moveOnLineY(player, screenPos); //右へ
	}
	else if (screenPos.dx >= player.center.dx
		&& screenPos.dx < WIN_WIDTH
		&& onScreenY(screenPos)) {
		pos.dx -= moveSpeed.dx * moveOnLineY(player, screenPos); //左へ
	}

	/* y方向の移動 */
	if (screenPos.dy >= 0
		&& screenPos.dy < player.center.dy
		&& onScreenX(screenPos)) {
		pos.dy += moveSpeed.dy * moveOnLineX(player, screenPos); //上へ
	}
	else if (screenPos.dy >= player.center.dy
		&& screenPos.dy < WIN_HEIGHT
		&& onScreenX(screenPos)) {
		pos.dy -= moveSpeed.dy * moveOnLineX(player, screenPos); //下へ
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player">プレイヤークラス</param>
/// <param name="pos">敵の座標</param>
/// <param name="screenPos">敵の画面上座標</param>
void EnemyTracking::update(Player& player, Vec2d& pos, Vec2d& screenPos) {
	getMoveSpeed(player, pos); //移動速度の取得
	move(player, pos, screenPos); //移動処理
}
