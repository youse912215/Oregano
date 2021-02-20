#pragma once
#include "mapDraw.h"
#include <vector>

using namespace std;

class MapCollision {
private:
	MapDraw& map;

	bool leftUpCollisionFlag();
	bool rightUpCollisionFlag();
	bool leftDownCollisionFlag();
	bool rightDownCollisionFlag();

public:
	MapCollision(MapDraw& map);
	~MapCollision();

	void update();
	bool leftCollisionFlag();
	bool rightCollisionFlag();
	bool upCollisionFlag();
	bool downCollisionFlag();
};
