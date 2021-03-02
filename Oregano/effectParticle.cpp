#include "effectParticle.h"
#include "random.h"
#include "DxLib.h"
#include <cmath>


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
	pos.dx = 0.0;
	pos.dy = 0.0;

	radius = 0.0;

	moveDistance = 0.0;

	generationTime = 0.0;

	lifeTime = false;
}

EffectParticle::~EffectParticle() {
}

void EffectParticle::setPosition(Vec2& deadPos) {
	/*moveDir(getRandomD(changeSign(0, 9), 3 * changeSign(0, 9)),
	        getRandomD(changeSign(0, 9), 3 * changeSign(0, 9)));*/

	movePos = generationTime * moveDir;

	pos += movePos;

	//moveDistance = pos - initPos;
	moveDistance = pos - deadPos;

	radius = (60.0 - generationTime) * moveSize / 10.0;

	if (abs(moveDistance.dx) >= 50.0 || abs(moveDistance.dy) >= 50.0) {
		generationTime = 0.0;
		/*pos.dx = initPos.dx;
		pos.dy = initPos.dy;*/
		pos.dx = deadPos.dx;
		pos.dy = deadPos.dy;
		lifeTime = false;
	}
}


void EffectParticle::occurrenceParticle(Vec2& deadPos) {
	generationTime++;

	setPosition(deadPos);

	/*DrawCircle(static_cast<int>(pos.dx), static_cast<int>(pos.dy),
	           static_cast<int>(radius),
	           GetColor(255, 0, 0), true);*/

	SetDrawBlendMode(DX_BLENDMODE_ADD, 158);


	DrawRotaGraph2(static_cast<int>(pos.dx) - static_cast<int>(radius),
	               static_cast<int>(pos.dy) - static_cast<int>(radius),
	               8, 8, radius / 5.0, getAngle(0, 360),
	               source.bloodGraph, true, false);

	DrawFormatString(400, 400, GetColor(255, 255, 255),
	                 "dx:%.1lf, dy:%.1lf, Time:%.1lf, L:%d", pos.dx, pos.dy,
	                 radius, lifeTime, false);
}

void EffectParticle::initProcess(Vec2& deadPos) {
	//pos = initPos;
	pos = deadPos;
	moveDir.dx = static_cast<double>(changeSign(0, 1)) * getRandomD(0, 360) / 360.0;
	moveDir.dy = static_cast<double>(changeSign(0, 1)) * getRandomD(0, 360) / 360.0;
	lifeTime = true;
}

void EffectParticle::update(std::vector<EffectParticle>& particles, Vec2& deadPos) {
	for (auto& i : particles) {
		if (!i.lifeTime) {
			i.initProcess(deadPos);
			break;
		}
		i.occurrenceParticle(deadPos);
	}
}
