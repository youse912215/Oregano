#pragma once
#include "dataSource.h"
#include "vec2.h"
#include <vector>

class EffectSpurt : public DataSource {
private:
	Vec2d pos; //���W
	Vec2d movePos;
	Vec2d moveDistance;
	double firstSpeed; //�����x
	double generationTime; //��������
	const double g; //�d�͉����x
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
