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
	double radius;
	double radian;
	bool isAlive;

public:

	EffectSpurt();
	~EffectSpurt();

	void draw();
	void initialize(Vec2d& deadPos);
	void occurrenceParticle(Vec2d& deadPos);
	void update(std::vector<EffectSpurt>& spurt, Vec2d& deadPos);
};
