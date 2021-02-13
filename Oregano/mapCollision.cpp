#include "mapCollision.h"
#include "constant.h"
#include "mapDraw.h"
#include "DxLib.h"

MapCollision::MapCollision(MapDraw& map) : map(map) {
}

void MapCollision::update() {

}

bool MapCollision::leftUpCollisionFlag() {
	return false;
}

bool MapCollision::rightUpCollisionFlag() {
	return false;
}

bool MapCollision::leftDownCollisionFlag() {
	return false;
}

bool MapCollision::rightDownCollisionFlag() {
	return false;
}

//--- 4方向（上下左右）の衝突判定の結果を返す ---//
bool MapCollision::leftCollisionFlag() {
	return (map.collisionFlag[LEFT_UP] && map.collisionFlag[CENTER_LEFT1]
			|| (map.collisionFlag[LEFT_DOWN] && map.collisionFlag[CENTER_LEFT2]))
		|| (map.collisionFlag[CENTER_LEFT1] && map.collisionFlag[CENTER_LEFT2]);
}

bool MapCollision::rightCollisionFlag() {
	return ((map.collisionFlag[RIGHT_UP] && map.collisionFlag[CENTER_RIGHT1])
		|| (map.collisionFlag[RIGHT_DOWN] && map.collisionFlag[CENTER_RIGHT2])
		|| (map.collisionFlag[CENTER_RIGHT1] && map.collisionFlag[CENTER_RIGHT2]));
}

bool MapCollision::upCollisionFlag() {
	return ((map.collisionFlag[LEFT_UP] && map.collisionFlag[CENTER_UP1])
		|| (map.collisionFlag[RIGHT_UP] && map.collisionFlag[CENTER_UP2])
		|| (map.collisionFlag[CENTER_UP1] && map.collisionFlag[CENTER_UP2]));
}

bool MapCollision::downCollisionFlag() {
	return ((map.collisionFlag[LEFT_DOWN] && map.collisionFlag[CENTER_DOWN1])
		|| (map.collisionFlag[RIGHT_DOWN] && map.collisionFlag[CENTER_DOWN2])
		|| (map.collisionFlag[CENTER_DOWN1] && map.collisionFlag[CENTER_DOWN2]));
}

//----------------------------------------//
