#include "enemy.h"
#include "DxLib.h"
#include "constant.h"
#include "random.h"
#include "mapDraw.h"
#include <cmath>

#include "enemyTracking.h"

EnemyTracking tracking;


Enemy::Enemy() :
	pos(0.0, 0.0), center(0.0, 0.0),
	screenCenter(0.0, 0.0), relativeDistance(0.0, 0.0), life(0), initLife{1, 2, 3}, possessionCoin{5, 15, 25},
	attackPower{5, 25, 50},
	level(0), damageInterval(2), damageFlag(2), attributeValue{15, 30, 50}, lissajousMaxTime(7200.0),

	lissajousX(800.0), lissajousY(450.0), controlSpeed(10.0), lissajousTime(0), lissajousRandom(0),

	pattern(0), screenPos(0.0, 0.0),

	deadTime(0), attribute(0),

	activity(false), deadFlag(false), intervalFlag(2) {

}

Enemy::~Enemy() {
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::draw(DataSource& source) {
	//属性（attribute）によって、画像を変更する
	DrawRectGraph(static_cast<int>(screenPos.dx),
	              static_cast<int>(screenPos.dy),
	              attribute * static_cast<int>(HALF_BLOCK_SIZE_D), 0,
	              static_cast<int>(HALF_BLOCK_SIZE_D), static_cast<int>(HALF_BLOCK_SIZE_D),
	              source.enemyGraph, true, false);
}

/// <summary>
/// 死亡処理
/// </summary>
void Enemy::dead() {
	deadFlag = true; //死亡状態をtrue
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
		takeDamage(KNIFE); //ダメージを受ける
	}
}

/// <summary>
/// 刃ヒット時の処理
/// </summary>
void Enemy::hitSlash() {
	//
	if (abs(relativeDistance.dx) <= 80.0 && abs(relativeDistance.dy) <= 80.0) {
		takeDamage(SLASH); //ダメージを受ける
	}
}

/// <summary>
/// ダメージを受ける
/// </summary>
/// <param name="act">プレイヤーのアクション</param>
void Enemy::takeDamage(const int& act) {
	if (damageInterval[act] == 0) {
		damageFlag[act] = true;
		intervalFlag[act] = true;
	}
}

/// <summary>
/// ダメージ処理
/// </summary>
/// <param name="act">プレイヤーのアクション</param>
void Enemy::damageProcess(Player& player, const int& act) {
	if (intervalFlag[act])
		damageInterval[act]++;

	if (damageInterval[act] >= 15) {
		damageInterval[act] = 0;
		intervalFlag[act] = false;
	}

	if (damageFlag[act]) {
		life -= player.addDamage(act);
		damageFlag[act] = false;
	}
}

/// <summary>
/// 0ライフの処理
/// </summary>
void Enemy::noLife(Player& player) {
	if (life <= 0) {
		life = 0;
		dead(); //死亡処理
		player.addPlayerCoin(attribute, possessionCoin[level]); //コイン追加処理
	}
}

/// <summary>
/// プレイヤーとの衝突処理
/// </summary>
void Enemy::collision(Player& player) {
	//プレイヤーとの距離がENEMY_COLLISION_DISTANCE以下のとき
	if (abs(relativeDistance.dx) <= ENEMY_COLLISION_DISTANCE
		&& abs(relativeDistance.dy) <= ENEMY_COLLISION_DISTANCE) {
		life = 0;
		//dead(); //死亡処理
		player.lostPlayerCoin(attackPower[level]); //(プレイヤーの)コインの損失処理
		player.addAttributeAccumulation(attribute, attributeValue[level]); //属性耐久値を加算
	}
}

/// <summary>
/// ステータスを設定
/// </summary>
void Enemy::setStatus() {
	pattern = getRandom(0, 1); //敵のパターンをランダムで生成
	lissajousRandom = getRandom(1, 15); //リサージュ曲線の種類をランダムで生成
	attribute = getRandom(0, 3); //属性値
	level = getRandom(0, 2); //レベル
	life = initLife[level]; //ライフ
}

/// <summary>
/// 死亡時間をカウント
/// </summary>
void Enemy::countDeadTime() {
	if (deadFlag) deadTime++;
	if (deadTime >= 30) {
		deadTime = 0;
		deadFlag = false;
	}
}

/// <summary>
/// リサージュ用の時間カウント処理
/// </summary>
void Enemy::countTime() {
	//lissajousTimeが7200（800と450の最小公倍数）より小さいとき、カウント
	lissajousTime = (lissajousTime < lissajousMaxTime) ? ++lissajousTime : 0;
}

/// <summary>
/// リサージュ曲線を描く
/// </summary>
void Enemy::lissajous() {
	lissajousSpeed.dx = sin(lissajousRandom * lissajousTime / lissajousX) * controlSpeed; //x方向
	lissajousSpeed.dy = cos(lissajousRandom * lissajousTime / lissajousY) * controlSpeed; //y方向
	pos += lissajousSpeed; //移動速度を加算
}

/// <summary>
/// 初期位置の取得
/// 現在のプレイヤーの位置から周辺にかけて出現
/// </summary>
void Enemy::initPosition(Player& player) {
	//x座標
	pos.dx = getPopLocation(ONE_MAP_X, //マップサイズ
	                        player.currentMapPos(MAP_X_), //全体マップ座標
	                        getRandom(AREA_MIN, AREA_MAX)); //1区画座標
	//y座標
	pos.dy = getPopLocation(ONE_MAP_Y, //マップサイズ
	                        player.currentMapPos(MAP_Y_), //全体マップ座標
	                        getRandom(AREA_MIN, AREA_MAX)); //1区画座標
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
void Enemy::update(Player& player, DataSource& source) {
	relativeDistanceUpdate(player); //プレイヤーとの相対距離を取得

	if (player.knife) hitKnife(player); //ナイフが当たったとき
	if (player.slash) hitSlash(); //刃が当たったとき

	damageProcess(player, KNIFE); //ナイフダメージ処理
	damageProcess(player, SLASH); //刃ダメージ処理

	noLife(player); //0ライフ処理

	countDeadTime(); //死亡時間をカウント

	if (activity) {
		collision(player); //プレイヤーとの衝突処理
		if (pattern % 2 == 0)
			tracking.update(player, pos, screenPos); //追跡移動の更新処理
		else {
			countTime(); //リサージュ用の時間カウント処理
			lissajous(); //リサージュ曲線描画
		}
		draw(source); //描画処理
	}

	//敵が画面サイズの2倍の範囲外にいるとき
	if (abs(relativeDistance.dx) >= WIN_WIDTH && abs(relativeDistance.dy) >= WIN_HEIGHT) {
		dead();
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
	                 "act：%d, dead:%d, dTime:%d, LIFE:%d, dm1:%d, dm2:%d",
	                 activity, deadFlag, deadTime, life,
	                 player.addDamage(0), player.addDamage(1), false);
}

void Enemy::initialize(Player& player) {
	initPosition(player); //初期位置の取得
	setStatus(); //ステータスを設定
	relativeDistanceUpdate(player); //プレイヤーとの相対距離を取得

	//敵が画面サイズの2倍の範囲内にいるとき
	if (abs(relativeDistance.dx) <= WIN_WIDTH && abs(relativeDistance.dy) <= WIN_HEIGHT) {
		activity = true; //活動状態をtrue
	}
}
