#include "effectSpurt.h"
#include "DxLib.h"
#include "random.h"
#include <cmath>

EffectSpurt::EffectSpurt() :
	pos(0.0, 0.0), movePos(0.0, 0.0), moveDistance(0.0, 0.0),
	radiusRange(5, 10), radianRange(60, 120), firstSpeed(5.0),
	generationTime(0.0), g(9.8), radius(5.0), radian(0.0), maxTime(10.0), maxRange(150.0),
	colorMax(255), isAlive(false) {
}

EffectSpurt::~EffectSpurt() {
}

void EffectSpurt::draw() {
	SetDrawBlendMode(DX_BLENDMODE_INVSRC, getRandom(0, colorMax)); //加算ブレンド

	/* 円の描画 */
	DrawCircle(static_cast<int>(pos.dx), static_cast<int>(pos.dy), static_cast<int>(radius),
	           //色はランダムで変更
	           GetColor(getRandom(0, colorMax),
	                    getRandom(0, colorMax),
	                    getRandom(0, colorMax)), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //ブレンドオフ
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="deadPos"敵が死んだ座標</param>
void EffectSpurt::initialize(Vec2d& deadPos) {
	pos = deadPos;
	radius = getRandomD(radiusRange.x, radiusRange.y); //半径をランダムで取得
	radian = getRadian(radianRange.x, radianRange.y); //ラジアンをランダムで取得
	isAlive = true; //生存状態をtrue
}

/// <summary>
/// パーティクル発生
/// </summary>
/// <param name="deadPos">敵が死んだ座標</param>
void EffectSpurt::occurrenceParticle(Vec2d& deadPos) {
	generationTime++; //生存時間をカウント

	movePos.dx = firstSpeed * cos(radian) * (generationTime / maxTime); //x方向の計算
	movePos.dy = firstSpeed * sin(radian) * (generationTime / maxTime)
		- (g * ((generationTime / maxTime) * (generationTime / maxTime))) / 2.0; //y方向の計算

	pos += movePos; //移動ポジジョンを加算
	moveDistance = pos - deadPos; //移動距離を計算

	/* 移動距離がmaxRangeのとき */
	if (abs(moveDistance.dy) >= maxRange) {
		generationTime = 0.0; //生存時間をリセット
		pos = deadPos; //ポジションをリセット
		isAlive = false; //生存状態をfalse
	}

	draw(); //描画処理
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="spurt">パーティクルの配列</param>
/// <param name="deadPos">敵が死んだ座標</param>
void EffectSpurt::update(std::vector<EffectSpurt>& spurt, Vec2d& deadPos) {
	for (auto& i : spurt) {
		//パーティクルが生存していないとき
		if (!i.isAlive) {
			i.initialize(deadPos); //初期化
			break; //抜け出す
		}
		i.occurrenceParticle(deadPos); //パーティクル発生
	}
}
