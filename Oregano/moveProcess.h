#pragma once
#include "mapDraw.h"
#include "mapCollision.h"

class MoveProcess {
private:
	bool mapCondition(MapDraw& draw, const int& mapInfo); //ğŒ
	int movingDistance(MapDraw& draw); //ˆÚ“®‹——£

public:
	void left(MapCollision& collision, MapDraw& draw); //¶ˆÚ“®
	void right(MapCollision& collision, MapDraw& draw); //‰EˆÚ“®
	void up(MapCollision& collision, MapDraw& draw); //ãˆÚ“®
	void down(MapCollision& collision, MapDraw& draw); //‰ºˆÚ“®


};
