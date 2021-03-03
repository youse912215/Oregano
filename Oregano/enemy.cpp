#include "enemy.h"
#include "DxLib.h"
#include "constant.h"
#include "random.h"

#include <cmath>

#include "mapDraw.h"


Enemy::Enemy() :
	pos(0.0, 0.0), center(0.0, 0.0),
	screenCenter(0.0, 0.0), relativeDistance(0.0, 0.0),

	attackPower(5), coin{5, 15, 25}, attribute(0), attributeValue{15, 30, 50},

	lissajousTime(0), lissajousRandom(0),

	screenPos(0.0, 0.0),

	activity(false), deadFlag(false), deadTime(0) {

}

Enemy::~Enemy() {
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::draw() {
	//DrawGraph(static_cast<int>(screenPos.dx), static_cast<int>(screenPos.dy), graph, true); //敵

	//属性（attribute）によって、画像を変更する
	DrawRectGraph(static_cast<int>(screenPos.dx),
	              static_cast<int>(screenPos.dy),
	              attribute * static_cast<int>(HALF_BLOCK_SIZE_D), 0,
	              static_cast<int>(HALF_BLOCK_SIZE_D), static_cast<int>(HALF_BLOCK_SIZE_D),
	              source.enemyGraph, true, false);
}

/// <summary>
/// 移動処理
/// プレイヤーの左か右かで移動方向が変化する
/// </summary>
void Enemy::move(Player& player) {
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
	deadFlag = true;
	activity = false; //活動状態をfalse
}

/// <summary>
/// プレイヤーとの相対距離の更新
/// </summary>
void Enemy::relativeDistanceUpdate(Player& player) {
	screenPos.dx = pos.dx - static_cast<double>(MapDraw::mapX); //画面上のx座標
	screenPos.dy = pos.dy - static_cast<double>(MapDraw::mapY); //画面上のy座標
	screenCenter = QUARTER_BLOCK_SIZE_D + screenPos; //画面上の中心座標
	relativeDistance = screenCenter - player.center; //プレイヤーとの相対距離

}

/// <summary>
/// ナイフヒット時の処理
/// </summary>
void Enemy::hitKnife(Player& player) {
	//ナイフとの相対距離がWEAPON_COLLISION_DISTANCE以下のとき
	if (abs(screenCenter.dx - player.knifeCenter.dx) <= WEAPON_COLLISION_DISTANCE
		&& abs(screenCenter.dy - player.knifeCenter.dy) <= WEAPON_COLLISION_DISTANCE) {
		dead(); //死亡処理
		player.addPlayerCoin(attribute, coin[0]); //コイン追加処理
	}
}

/// <summary>
/// 刃ヒット時の処理
/// </summary>
void Enemy::hitSlash(Player& player) {
	//
	if (abs(relativeDistance.dx) <= 80.0 && abs(relativeDistance.dy) <= 80.0) {
		dead(); //死亡処理
		player.addPlayerCoin(attribute, coin[0]); //コイン追加処理
	}
}

/// <summary>
/// プレイヤーとの衝突処理
/// </summary>
void Enemy::collision(Player& player) {
	//プレイヤーとの距離がENEMY_COLLISION_DISTANCE以下のとき
	if (abs(relativeDistance.dx) <= ENEMY_COLLISION_DISTANCE
		&& abs(relativeDistance.dy) <= ENEMY_COLLISION_DISTANCE) {
		dead(); //死亡処理
		player.lostPlayerCoin(attackPower); //(プレイヤーの)コインの損失処理
		player.addAttributeAccumulation(attribute, attributeValue[0]);
	}
}

/// <summary>
/// プレイヤーとの位置関係から移動速度を得る
/// </summary>
void Enemy::getMoveSpeed(Player& player) {
	distance = player.center - (QUARTER_BLOCK_SIZE_D + pos); //距離
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

void Enemy::getAttribute() {
	attribute = getRandom(0, 3);
}

void Enemy::countDeadTime() {
	if (deadFlag) deadTime++;
	if (deadTime >= 30) {
		deadTime = 0;
		deadFlag = false;
	}
}

void Enemy::lissajous() {
	lissajousTime++;
	movePattern2.dx = sin(lissajousRandom * lissajousTime / 800) * 10;
	movePattern2.dy = cos(lissajousRandom * lissajousTime / 450) * 10;
	pos += movePattern2;
}

/// <summary>
/// 初期位置の取得
/// </summary>
void Enemy::initPosition() {
	pos.dx = getPopLocation(ONE_MAP_X, 3, getRandom(AREA_MIN, AREA_MAX)); //x座標
	pos.dy = getPopLocation(ONE_MAP_Y, 3, getRandom(AREA_MIN, AREA_MAX)); //y座標
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
void Enemy::update(Player& player) {
	relativeDistanceUpdate(player); //プレイヤーとの相対距離を取得

	if (player.knife) hitKnife(player); //ナイフが当たったとき
	if (player.slash) hitSlash(player); //刃が当たったとき

	countDeadTime();

	if (activity) {
		collision(player); //プレイヤーとの衝突処理
		getMoveSpeed(player); //移動速度取得
		move(player); //移動処理
		//lissajous();
		draw(); //描画処理
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
	DrawFormatString(200, 230, GetColor(0, 0, 255),
	                 "act：%d, dead:%d, dTime:%d",
	                 activity, deadFlag, deadTime, false);
	DrawFormatString(200, 260, GetColor(0, 0, 255),
	                 "slash:%d",
	                 player.slash, false);
}

void Enemy::initProcess(Player& player) {
	initPosition(); //初期位置の取得
	getAttribute();
	relativeDistanceUpdate(player); //プレイヤーとの相対距離を取得
	lissajousRandom = getRandom(1, 15);
	if (abs(relativeDistance.dx) <= 500 && abs(relativeDistance.dy) <= 500) {
		activity = true;
	}
}
