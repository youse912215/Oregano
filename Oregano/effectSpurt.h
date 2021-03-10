#pragma once
#include "dataSource.h"
#include "vec2.h"
#include <vector>

class EffectSpurt : public DataSource {
private:
	Vec2d pos; //座標
	Vec2d movePos; //移動座標
	Vec2d moveDistance; //移動距離
	Vec2 radiusRange; //半径範囲
	Vec2 radianRange; //ラジアン範囲

	double firstSpeed; //初速度
	double generationTime; //発生時間
	const double g; //重力加速度
	double radius; //半径
	double radian; //ラジアン

	const double maxTime; //最大時間
	const double maxRange; //最大範囲
	const int colorMax; //色の最大RGB

	bool isAlive; //生存状態

	void draw(); //描画処理
	void initialize(Vec2d& deadPos); //初期化
	void occurrenceParticle(Vec2d& deadPos); //パーティクル発生

public:
	EffectSpurt();
	~EffectSpurt();

	void update(std::vector<EffectSpurt>& spurt, Vec2d& deadPos); //更新処理
};
