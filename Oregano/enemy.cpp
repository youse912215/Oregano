#include "enemy.h"
#include "DxLib.h"
#include "constant.h"
#include "random.h"
#include <cmath>

#include "mapDraw.h"

Enemy::Enemy(int graph, Player& player) : player(player), graph(graph) {
	this->pos.dx = getPopLocation(ONE_MAP_X, 7/*get_random(4, TOTAL_MAPS_X - 1)*/, get_random(AREA_MIN, AREA_MAX));
	this->pos.dy = getPopLocation(ONE_MAP_Y, 7/*get_random(5, TOTAL_MAPS_Y - 1)*/, get_random(AREA_MIN, AREA_MAX));
	this->center = QUARTER_BLOCK_SIZE + pos;
	screenPos = 0;
	screenCenter = 0;
	relativeDistance = 0;

	attackPower = 5;

	activity = false;
	alive = true;
}

Enemy::~Enemy() {
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::draw() {
	DrawGraph(static_cast<int>(screenPos.dx), static_cast<int>(screenPos.dy), graph, true); //敵
}

/// <summary>
/// 移動処理
/// プレイヤーの左か右かで移動方向が変化する
/// </summary>
void Enemy::move() {
	/* x方向の移動 */
	if (screenPos.dx >= 0
		&& screenPos.dx < player.center.dx
		&& onScreenY()) {
		this->pos.dx += moveSpeed.dx; //右へ
	}
	else if (screenPos.dx >= player.center.dx
		&& screenPos.dx < WIN_WIDTH
		&& onScreenY()) {
		this->pos.dx -= moveSpeed.dx; //左へ
	}

	/* y方向の移動 */
	if (screenPos.dy >= 0
		&& screenPos.dy < player.center.dy
		&& onScreenX()) {
		this->pos.dy += moveSpeed.dy; //上へ
	}
	else if (screenPos.dy >= player.center.dy
		&& screenPos.dy < WIN_HEIGHT
		&& onScreenX()) {
		this->pos.dy -= moveSpeed.dy; //下へ
	}
}

/// <summary>
/// 死亡処理
/// </summary>
void Enemy::dead() {
	activity = false; //活動状態をfalse
	alive = false; //生存状態をfalse
}

/// <summary>
/// プレイヤーとの相対距離の更新
/// </summary>
void Enemy::relativeDistanceUpdate() {
	screenPos.dx = pos.dx - static_cast<double>(MapDraw::mapX); //画面上のx座標
	screenPos.dy = pos.dy - static_cast<double>(MapDraw::mapY); //画面上のy座標
	screenCenter = QUARTER_BLOCK_SIZE + screenPos; //画面上の中心座標
	relativeDistance = screenCenter - player.center; //プレイヤーとの相対距離

}

/// <summary>
/// ナイフヒット時の処理
/// </summary>
void Enemy::hitKnife() {
	//ナイフとの相対距離がWEAPON_COLLISION_DISTANCE以下のとき
	if (abs(screenCenter.dx - player.knifeCenter.dx) <= WEAPON_COLLISION_DISTANCE
		&& abs(screenCenter.dy - player.knifeCenter.dy) <= WEAPON_COLLISION_DISTANCE) {
		dead(); //死亡処理
	}
}

/// <summary>
/// 刃ヒット時の処理
/// </summary>
void Enemy::hitSlash() {
	//
	if (abs(relativeDistance.dx) <= 80.0 && abs(relativeDistance.dy) <= 80.0) {
		dead(); //死亡処理
	}
}

/// <summary>
/// プレイヤーとの衝突処理
/// </summary>
void Enemy::collision() {
	//プレイヤーとの距離がENEMY_COLLISION_DISTANCE以下のとき
	if (abs(relativeDistance.dx) <= ENEMY_COLLISION_DISTANCE
		&& abs(relativeDistance.dy) <= ENEMY_COLLISION_DISTANCE) {
		dead(); //死亡処理
		player.lostPlayerCoin(attackPower);
	}
}

/// <summary>
/// プレイヤーとの位置関係から移動速度を得る
/// </summary>
void Enemy::getMoveSpeed() {
	distance = player.center - this->center; //距離
	distanceSquared = distance * distance; //距離の2乗
	distanceNormalized.dx = abs(distance.dx) / sqrt(distanceSquared.dx + distanceSquared.dy); //x方向の正規化
	distanceNormalized.dy = abs(distance.dy) / sqrt(distanceSquared.dx + distanceSquared.dy); //y方向の正規化
	moveSpeed = 4 * distanceNormalized; //移動速度
}

/// <summary>
/// 画面上のx座標にいる条件
/// </summary>
bool Enemy::onScreenX() {
	return screenPos.dx >= 0 && screenPos.dx <= WIN_WIDTH;
}

/// <summary>
/// 画面上のy座標にいる条件
/// </summary>
bool Enemy::onScreenY() {
	return screenPos.dy >= 0 && screenPos.dy <= WIN_HEIGHT;
}

/// <summary>
/// 初期位置の取得
/// </summary>
void Enemy::initPosition() {
	pos.dx = getPopLocation(ONE_MAP_X, get_random(7, TOTAL_MAPS_X - 1), get_random(AREA_MIN, AREA_MAX)); //x座標
	pos.dy = getPopLocation(ONE_MAP_Y, get_random(8, TOTAL_MAPS_Y - 1), get_random(AREA_MIN, AREA_MAX)); //y座標
}

/// <summary>
/// 出現位置を取得
/// </summary>
/// <param name="mapDir">xまたはyのマップサイズ</param>
/// <param name="coordinate1">全体マップの座標</param>
/// <param name="coordinate2">1区画の座標</param>
double Enemy::getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2) {
	return mapDir * coordinate1 + BLOCK_SIZE * coordinate2;
}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::update() {
	relativeDistanceUpdate(); //プレイヤーとの相対距離を取得

	if (player.knife) hitKnife(); //ナイフが当たったとき
	if (player.slash) hitSlash(); //刃が当たったとき

	//敵が生きているとき
	if (activity) {
		collision(); //プレイヤーとの衝突処理
		getMoveSpeed(); //移動速度取得
		move(); //移動処理
		draw(); //描画処理
	}
	else {
		initPosition(); //初期位置の取得
		if (abs(relativeDistance.dx) <= 500 || abs(relativeDistance.dy) <= 500 && alive) activity = true;
	}

	DrawFormatString(200, 185, GetColor(0, 0, 255),
	                 "En座標：%lf, %lf",
	                 pos.dx, pos.dy, false);
	DrawFormatString(200, 200, GetColor(0, 0, 255),
	                 "スクリーン座標：%lf, %lf",
	                 screenPos.dx, screenPos.dy, false);
	DrawFormatString(200, 215, GetColor(0, 0, 255),
	                 "相対座標：%lf, %lf",
	                 abs(relativeDistance.dx),
	                 abs(relativeDistance.dy), false);

}
