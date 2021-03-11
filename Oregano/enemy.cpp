#include "enemy.h"
#include "DxLib.h"
#include "constant.h"
#include "random.h"
#include "mapDraw.h"
#include "enemyTracking.h"
#include <cmath>

EnemyTracking tracking; //追跡クラス

Enemy::Enemy() :
	pos(0.0, 0.0), center(0.0, 0.0),
	screenCenter(0.0, 0.0), relativeDistance(0.0, 0.0), lifeHeight(8), intervalMax(15), initLife{1, 2, 3, 4},
	possessionCoin{1, 2, 3, 4}, attackPower{2, 6, 10, 14}, attributeValue{2, 3, 4, 5}, life(0),

	pattern(0), level(0), maxLevel(4), damageInterval(2), damageFlag(2), knifeRange(80.0), deadTimeMax(40),

	lissajousMaxTime(7200.0), lissajousX(800.0), lissajousY(450.0), controlSpeed(10.0), lissajousTime(0),

	lissajousRandom(0), screenPos(0.0, 0.0),

	deadTime(0), attribute(0),

	activity(false), deadFlag(false), intervalFlag(2) {

}

Enemy::~Enemy() {
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::draw(DataSource& source) {
	/*属性（attribute）によって、画像を変更する*/
	DrawRectGraph(static_cast<int>(screenPos.dx),
	              static_cast<int>(screenPos.dy),
	              attribute * static_cast<int>(HALF_BLOCK_SIZE_D), 0,
	              static_cast<int>(HALF_BLOCK_SIZE_D), static_cast<int>(HALF_BLOCK_SIZE_D),
	              source.enemyGraph, true, false); //敵
	/* lifeによって、画像を変更する */
	DrawRectGraph(static_cast<int>(screenPos.dx),
	              static_cast<int>(screenPos.dy) - 10,
	              0, life * lifeHeight - lifeHeight,
	              static_cast<int>(HALF_BLOCK_SIZE_D), lifeHeight,
	              source.enemyLife, true, false); //life
}

/// <summary>
/// 死亡処理
/// </summary>
void Enemy::dead() {
	activity = false; //活動状態をfalse
	deadFlag = true; //死亡状態をtrue
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
	//knifeRange以下なら
	if (abs(relativeDistance.dx) <= knifeRange && abs(relativeDistance.dy) <= knifeRange) {
		takeDamage(SLASH); //ダメージを受ける
	}
}

/// <summary>
/// ダメージを受ける
/// </summary>
/// <param name="act">プレイヤーのアクション</param>
void Enemy::takeDamage(const int& act) {
	if (damageInterval[act] == 0) {
		damageFlag[act] = true; //ダメージフラグをtrue
		intervalFlag[act] = true; //間隔フラグをtrue
	}
}

/// <summary>
/// ダメージ処理
/// </summary>
/// <param name="act">プレイヤーのアクション</param>
void Enemy::damageProcess(Player& player, const int& act, DataSource& source) {
	/* 間隔フラグがtrueのとき */
	if (intervalFlag[act])
		damageInterval[act]++; //ダメージ間隔時間をカウント

	/* ダメージ間隔時間がintervalMax異常なら */
	if (damageInterval[act] >= intervalMax) {
		damageInterval[act] = 0; //ダメージ間隔時間を0
		intervalFlag[act] = false; //間隔フラグをfalse
	}

	/* ダメージフラグがtrueのとき */
	if (damageFlag[act]) {
		life -= player.addDamage(act); //ダメージ
		source.playSe(source.seHit); //ヒットSE
		damageFlag[act] = false; //ダメージフラグをfalse
	}
}

/// <summary>
/// 0ライフの処理
/// </summary>
void Enemy::noLife(Player& player) {
	if (life <= 0) {
		life = 0; //ライフを0にする
		player.addPlayerCoin(attribute, possessionCoin[level]); //コイン追加処理
		dead(); //死亡処理
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
		player.lostPlayerCoin(attackPower[level]); //(プレイヤーの)コインの損失処理
		player.addAttributeAccumulation(attribute, attributeValue[level]); //属性耐久値を加算
	}
}

/// <summary>
/// ステータスを設定
/// </summary>
void Enemy::setStatus() {
	pattern = getRandom(0, maxLevel); //敵のパターンをランダムで生成
	lissajousRandom = getRandom(1, 15); //リサージュ曲線の種類をランダムで15種類生成
	attribute = getRandom(0, maxLevel - 1); //属性値
	level = getRandom(0, maxLevel - 1); //レベル
	life = initLife[level]; //ライフ
}

/// <summary>
/// 死亡時間をカウント
/// </summary>
void Enemy::countDeadTime() {
	if (deadFlag) deadTime++; //時間をカウント

	//deadTimeMaxが経過したら
	if (deadTime >= deadTimeMax) {
		deadTime = 0; //死亡時間をリセット
		deadFlag = false; //死亡フラグをfalse
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
	                        player.currentMapPos(POSITION_X), //全体マップ座標
	                        getRandom(AREA_MIN, AREA_MAX)); //1区画座標
	//y座標
	pos.dy = getPopLocation(ONE_MAP_Y, //マップサイズ
	                        player.currentMapPos(POSITION_Y), //全体マップ座標
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

	countDeadTime(); //死亡時間をカウント

	/* 活動状態のとき */
	if (activity) {
		collision(player); //プレイヤーとの衝突処理

		if (player.actionFlag[KNIFE]) hitKnife(player); //ナイフが当たったとき
		if (player.actionFlag[SLASH]) hitSlash(); //刃が当たったとき

		damageProcess(player, KNIFE, source); //ナイフダメージ処理
		damageProcess(player, SLASH, source); //刃ダメージ処理

		//ランダムパターンが偶数なら
		if (pattern % 2 == 0) {
			countTime(); //リサージュ用の時間カウント処理
			lissajous(); //リサージュ曲線描画
		}
		else {
			tracking.update(player, pos, screenPos); //追跡移動の更新処理
		}

		draw(source); //描画処理

		noLife(player); //0ライフ処理	
	}

	//敵が画面サイズの2倍の範囲外にいるとき
	if (abs(relativeDistance.dx) >= WIN_WIDTH && abs(relativeDistance.dy) >= WIN_HEIGHT) {
		screenPos = -500.0; //画面外にポジションをセット
		dead(); //死亡処理
	}
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
