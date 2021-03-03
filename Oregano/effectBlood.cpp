#include "effectBlood.h"
#include "random.h"
#include "DxLib.h"
#include <cmath>

EffectBlood::EffectBlood() :
	movePos(10.0, 10.0), moveDir(1.0, 1.0),
	pos(0.0, 0.0), moveDistance(0.0, 0.0), radius(0.0),

	moveSize(1.5), isAlive(false), generationTime(0.0),
	graphSize(8), minRand(0), maxRand(360), maxRange(50.0), maxTime(180.0),
	color{green, yellow, blue, red} {
}

EffectBlood::~EffectBlood() {
}

/// <summary>
/// ポジションをセット
/// </summary>
/// <param name="deadPos"></param>
void EffectBlood::setPosition(Vec2d& deadPos) {
	movePos = generationTime * moveDir; //移動量を計算
	pos += movePos; //移動
	moveDistance = pos - deadPos; //発生ポジジョンからの距離を計算
	radius = (maxTime - generationTime) * moveSize / 10.0; //半径を計算

	/* 発生場所からmaxRange以上のとき */
	if (abs(moveDistance.dx) >= maxRange || abs(moveDistance.dy) >= maxRange) {
		generationTime = 0.0; //発生時間をリセット
		pos = deadPos; //ポジションをリセット
		isAlive = false; //生存状態をfalse
	}
}

/// <summary>
/// パーティクル発生
/// </summary>
/// <param name="deadPos">敵が死んだ座標</param>
/// <param name="attribute">敵の属性</param>
void EffectBlood::occurrenceParticle(Vec2d& deadPos, const int& attribute) {
	generationTime++; //発生時間をカウント
	setPosition(deadPos); //ポジションをセット
	draw(attribute); //描画処理
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="attribute">敵の属性</param>
void EffectBlood::draw(const int& attribute) {
	SetDrawBlendMode(DX_BLENDMODE_ADD, 150); //加算ブレンド

	/* 素材の描画 */
	DrawRotaGraph2(static_cast<int>(pos.dx) - static_cast<int>(radius),
	               static_cast<int>(pos.dy) - static_cast<int>(radius),
	               8, 8, radius / 5.0, getRadian(minRand, maxRand),
	               //敵のattributeによって色が変化
	               color[attribute], true, false);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //ブレンドオフ
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="deadPos">敵が死んだ座標</param>
void EffectBlood::initialize(Vec2d& deadPos) {
	pos = deadPos; //ポジジョンセット

	/* ランダムで方向を切り替える */
	moveDir.dx = static_cast<double>(changeSign(minRand, maxRand)) * getRandomD(minRand, maxRand) / maxTime;
	moveDir.dy = static_cast<double>(changeSign(minRand, maxRand)) * getRandomD(minRand, maxRand) / maxTime;

	isAlive = true; //パーティクルの生存状態をtrue
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="particles">パーティクルの配列</param>
/// <param name="deadPos">敵が死んだ座標</param>
/// <param name="attribute">敵の属性</param>
void EffectBlood::update(std::vector<EffectBlood>& particles, Vec2d& deadPos, const int& attribute) {
	for (auto& i : particles) {
		//パーティクルが生存していないとき
		if (!i.isAlive) {
			i.initialize(deadPos); //初期化
			break; //抜け出す
		}
		i.occurrenceParticle(deadPos, attribute); //パーティクル発生
	}
}
