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
	activity = false;
	alive = true;
}

Enemy::~Enemy() {
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::draw() {
	DrawGraph(static_cast<int>(screenPosX()), static_cast<int>(screenPosY()), graph, true);
}

/// <summary>
/// 移動処理
/// プレイヤーの左か右かで移動方向が変化する
/// </summary>
void Enemy::move() {
	/* x方向の移動 */
	if (screenPosX() >= 0
		&& screenPosX() < player.center.dx
		&& onScreenY()) {
		this->pos.dx += moveSpeed.dx;
	}
	else if (screenPosX() >= player.center.dx
		&& screenPosX() < WIN_WIDTH
		&& onScreenY()) {
		this->pos.dx -= moveSpeed.dx;
	}

	/* y方向の移動 */
	if (screenPosY() >= 0
		&& screenPosY() < player.center.dy
		&& onScreenX()) {
		this->pos.dy += moveSpeed.dy;
	}
	else if (screenPosY() >= player.center.dy
		&& screenPosY() < WIN_HEIGHT
		&& onScreenX()) {
		this->pos.dy -= moveSpeed.dy;
	}
}

/// <summary>
/// 死亡処理
/// </summary>
void Enemy::dead() {
	activity = false;
	alive = false;
}

void Enemy::destroying() {
	if (abs(screenPosX() + (HALF_BLOCK_SIZE / 2.0) - player.knifeCenter.dx) <= WEAPON_COLLISION_DISTANCE
		&& abs(screenPosY() + (HALF_BLOCK_SIZE / 2.0) - player.knifeCenter.dy) <= WEAPON_COLLISION_DISTANCE) {
		dead();
	}
}

/// <summary>
/// プレイヤーとの衝突処理
/// </summary>
void Enemy::collision() {
	if (relativeDistanceX() <= ENEMY_COLLISION_DISTANCE
		&& relativeDistanceY() <= ENEMY_COLLISION_DISTANCE) {
		dead();
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
/// 画面上のx座標
/// </summary>
double Enemy::screenPosX() {
	return pos.dx - static_cast<double>(MapDraw::mapX);
}

/// <summary>
/// 画面上のy座標
double Enemy::screenPosY() {
	return pos.dy - static_cast<double>(MapDraw::mapY);
}

/// <summary>
/// プレイヤーとの相対距離（x方向）
/// </summary>
double Enemy::relativeDistanceX() {
	return abs(screenPosX() + QUARTER_BLOCK_SIZE - player.center.dx);
}

/// <summary>
/// プレイヤーとの相対距離（y方向）
/// </summary>
double Enemy::relativeDistanceY() {
	return abs(screenPosY() + QUARTER_BLOCK_SIZE - player.center.dy);
}

/// <summary>
/// 画面上のx座標にいる条件
/// </summary>
bool Enemy::onScreenX() {
	return screenPosX() >= 0 && screenPosX() <= WIN_WIDTH;
}

/// <summary>
/// 画面上のy座標にいる条件
/// </summary>
bool Enemy::onScreenY() {
	return screenPosY() >= 0 && screenPosY() <= WIN_HEIGHT;
}

void Enemy::initPosition() {
	pos.dx = getPopLocation(ONE_MAP_X, get_random(7, TOTAL_MAPS_X - 1), get_random(AREA_MIN, AREA_MAX));
	pos.dy = getPopLocation(ONE_MAP_Y, get_random(8, TOTAL_MAPS_Y - 1), get_random(AREA_MIN, AREA_MAX));
}

double Enemy::getPopLocation(const int& dir, const int& x1, const int& x2) {
	return dir * x1 + BLOCK_SIZE * x2;
}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::update() {
	if (player.knife) destroying();

	//敵が生きているとき
	if (activity) {
		collision(); //プレイヤーとの衝突処理
		getMoveSpeed(); //移動速度取得
		move(); //移動処理
		draw(); //描画処理
	}
	else {
		initPosition();
		if (relativeDistanceX() <= 500 || relativeDistanceY() <= 500 && alive) activity = true;
	}

	DrawFormatString(200, 185, GetColor(0, 0, 255),
	                 "En座標：%lf, %lf",
	                 pos.dx, pos.dy, false);
	DrawFormatString(200, 200, GetColor(0, 0, 255),
	                 "スクリーン座標：%lf, %lf",
	                 screenPosX(), screenPosY(), false);
	DrawFormatString(200, 215, GetColor(0, 0, 255),
	                 "相対座標：%lf, %lf",
	                 abs(screenPosX() + (HALF_BLOCK_SIZE / 2.0) - player.knifeCenter.dx),
	                 abs(screenPosY() + (HALF_BLOCK_SIZE / 2.0) - player.knifeCenter.dy), false);

}
