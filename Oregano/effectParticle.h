#pragma once
#include "vec2.h"
#include "dataSource.h"
#include <vector>

class EffectParticle {
private:
	Vec2 movePos;
	Vec2 moveDir;
	Vec2 pos;
	Vec2 initPos;
	Vec2 moveDistance;

	DataSource source;

	double radius;

	double moveSize;


	void setPosition(Vec2& deadPos);

public:
	EffectParticle();
	~EffectParticle();

	bool lifeTime;
	double generationTime;

	void occurrenceParticle(Vec2& deadPos);
	void initProcess(Vec2& deadPos);

	void update(std::vector<EffectParticle>& particles, Vec2& deadPos);

};
