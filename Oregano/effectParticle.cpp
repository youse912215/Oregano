#include "effectParticle.h"
#include "random.h"
#include "DxLib.h"
#include <cmath>

double EffectParticle::generationTime = 0.0;

EffectParticle::EffectParticle() {
	initPos.dx = 400.0;
	initPos.dy = 400.0;

	moveSize = 1.5;
	//movePos(10.0, 10.0);

	movePos.dx = 10.0;
	movePos.dy = 10.0;

	//moveDir(1.0, 1.0);

	moveDir.dx = 1.0;
	moveDir.dy = 1.0;

	//pos(400.0, 400.0);
	pos.dx = 400.0;
	pos.dy = 400.0;

	radius = 0.0;

	moveDistance = 0.0;

	lifeTime = false;
}

EffectParticle::~EffectParticle() {
}

void EffectParticle::setPosition() {
	/*moveDir(getRandomD(changeSign(0, 9), 3 * changeSign(0, 9)),
	        getRandomD(changeSign(0, 9), 3 * changeSign(0, 9)));*/

	movePos = (generationTime / 10.0) * moveDir;

	pos += movePos;

	moveDistance = pos - initPos;

	radius = (40.0 - generationTime) * moveSize / 10.0;

	if (abs(moveDistance.dx) >= 50.0 || abs(moveDistance.dy) >= 50.0) {
		generationTime = 0.0;
		pos.dx = 400.0;
		pos.dy = 400.0;
		lifeTime = false;
	}
}


void EffectParticle::update() {
	generationTime++;

	setPosition();

	DrawCircle(static_cast<int>(pos.dx), static_cast<int>(pos.dy),
	           static_cast<int>(radius),
	           GetColor(255, 0, 0), true);

	DrawFormatString(400, 400, GetColor(255, 255, 255),
	                 "dx:%.1lf, dy:%.1lf, Time:%.1lf, L:%d", pos.dx, pos.dy,
	                 generationTime, lifeTime, false);
}

void EffectParticle::initProcess() {
	pos = initPos;
	moveDir.dx = static_cast<double>(changeSign(0, 9)) * getRandomD(0, 36) / 36.0;
	moveDir.dy = static_cast<double>(changeSign(0, 9)) * getRandomD(0, 36) / 36.0;
	lifeTime = true;
}
