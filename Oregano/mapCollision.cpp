#include "mapCollision.h"
#include "constant.h"
#include "mapDraw.h"
#include "DxLib.h"

MapCollision::MapCollision(MapDraw& map) : map(map) {
}

void MapCollision::update() {

}

//左上（3点）方向の衝突判定
bool MapCollision::leftUpCollisionFlag() {
	return map.collisionFlag[LEFT_UP] && map.collisionFlag[CENTER_UP1] && map.collisionFlag[CENTER_LEFT1];
}

//右上（3点）方向の衝突判定
bool MapCollision::rightUpCollisionFlag() {
	return map.collisionFlag[RIGHT_UP] && map.collisionFlag[CENTER_UP2] && map.collisionFlag[CENTER_RIGHT1];
}

//左下（3点）方向の衝突判定
bool MapCollision::leftDownCollisionFlag() {
	return map.collisionFlag[LEFT_DOWN] && map.collisionFlag[CENTER_DOWN1] && map.collisionFlag[CENTER_LEFT2];
}

//右下（3点）方向の衝突判定
bool MapCollision::rightDownCollisionFlag() {
	return map.collisionFlag[RIGHT_DOWN] && map.collisionFlag[CENTER_DOWN2] && map.collisionFlag[CENTER_RIGHT2];
}

//--- 4方向（上下左右）の衝突判定の結果を返す ---//
//左方向
bool MapCollision::leftCollisionFlag() {
	return ((map.collisionFlag[LEFT_UP] && map.collisionFlag[CENTER_LEFT1])
		|| (map.collisionFlag[LEFT_DOWN] && map.collisionFlag[CENTER_LEFT2])
		|| (map.collisionFlag[CENTER_LEFT1] && map.collisionFlag[CENTER_LEFT2])
		|| leftUpCollisionFlag()
		|| leftDownCollisionFlag());
}

//右方向
bool MapCollision::rightCollisionFlag() {
	return ((map.collisionFlag[RIGHT_UP] && map.collisionFlag[CENTER_RIGHT1])
		|| (map.collisionFlag[RIGHT_DOWN] && map.collisionFlag[CENTER_RIGHT2])
		|| (map.collisionFlag[CENTER_RIGHT1] && map.collisionFlag[CENTER_RIGHT2])
		|| rightUpCollisionFlag()
		|| rightDownCollisionFlag());
}

//上方向
bool MapCollision::upCollisionFlag() {
	return ((map.collisionFlag[LEFT_UP] && map.collisionFlag[CENTER_UP1])
		|| (map.collisionFlag[RIGHT_UP] && map.collisionFlag[CENTER_UP2])
		|| (map.collisionFlag[CENTER_UP1] && map.collisionFlag[CENTER_UP2])
		|| leftUpCollisionFlag()
		|| rightUpCollisionFlag());
}

//下方向
bool MapCollision::downCollisionFlag() {
	return ((map.collisionFlag[LEFT_DOWN] && map.collisionFlag[CENTER_DOWN1])
		|| (map.collisionFlag[RIGHT_DOWN] && map.collisionFlag[CENTER_DOWN2])
		|| (map.collisionFlag[CENTER_DOWN1] && map.collisionFlag[CENTER_DOWN2])
		|| leftDownCollisionFlag()
		|| rightDownCollisionFlag());
}

//----------------------------------------//
