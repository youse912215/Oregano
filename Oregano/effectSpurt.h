#pragma once
#include "dataSource.h"
#include "vec2.h"
#include <vector>

class EffectSpurt : public DataSource {
private:
	Vec2d pos; //座標
	Vec2d movePos;
	Vec2d moveDistance;
	double firstSpeed; //初速度
	double generationTime; //発生時間
	const double g; //重力加速度
	double radius; //半径
	double radian; //ラジアン
	bool isAlive; //生存状態

	void draw(); //描画処理
	void initialize(Vec2d& deadPos); //初期化
	void occurrenceParticle(Vec2d& deadPos); //パーティクル発生

public:
	EffectSpurt();
	~EffectSpurt();

	void update(std::vector<EffectSpurt>& spurt, Vec2d& deadPos); //更新処理
};
