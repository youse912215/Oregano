#pragma once
#include "vec2.h"

class EffectParticle {
private:
	Vec2 movePos;
	Vec2 moveDir;
	Vec2 pos;
	Vec2 initPos;
	Vec2 moveDistance;

	double radius;

	double moveSize;


	void setPosition();

public:
	EffectParticle();
	~EffectParticle();

	bool lifeTime;
	static double generationTime;

	void update();
	void initProcess();
};
