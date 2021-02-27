#include "mapCollision.h"
#include "constant.h"
#include "mapDraw.h"
#include "eventBase.h"

MapCollision::MapCollision(MapDraw& map) : map(map), collisionFlag(12),
                                           boundaryCriteria{
	                                           //左条件
	                                           map.currentCorner[LEFT] == AREA_MAX && map.currentCorner[RIGHT] ==
	                                           AREA_MIN
	                                           && map.currentMap.x >= map.currentBoundaryMap1.x && map.currentMap.x ==
	                                           map.currentBoundaryMap2.x,
	                                           //右条件
	                                           map.currentCorner[LEFT] == AREA_MAX && map.currentCorner[RIGHT] ==
	                                           AREA_MIN
	                                           && map.currentMap.x == map.currentBoundaryMap1.x && map.currentMap.x <=
	                                           map.currentBoundaryMap2.x,
	                                           //上条件
	                                           map.currentCorner[UP] == AREA_MAX && map.currentCorner[DOWN] == AREA_MIN
	                                           && map.currentMap.y >= map.currentBoundaryMap1.y && map.currentMap.y ==
	                                           map.currentBoundaryMap2.y,
	                                           //下条件
	                                           map.currentCorner[UP] == AREA_MAX && map.currentCorner[DOWN] == AREA_MIN
	                                           && map.currentMap.y == map.currentBoundaryMap1.y && map.currentMap.y <=
	                                           map.currentBoundaryMap2.y,
	                                           //中央横1条件
	                                           map.currentCorner[CENTER_X1] == AREA_MAX && map.currentCorner[CENTER_X2]
	                                           == AREA_MIN
	                                           && map.currentMap.x >= map.currentBoundaryMap1.x && map.currentMap.x ==
	                                           map.currentBoundaryMap2.x,
	                                           //中央横2条件
	                                           map.currentCorner[CENTER_X1] == AREA_MAX && map.currentCorner[CENTER_X2]
	                                           == AREA_MIN
	                                           && map.currentMap.x == map.currentBoundaryMap1.x && map.currentMap.x <=
	                                           map.currentBoundaryMap2.x,
	                                           //中央縦1条件
	                                           map.currentCorner[CENTER_Y1] == AREA_MAX && map.currentCorner[CENTER_Y2]
	                                           == AREA_MIN
	                                           && map.currentMap.y >= map.currentBoundaryMap1.y && map.currentMap.y ==
	                                           map.currentBoundaryMap2.y,
	                                           //中央縦2条件
	                                           map.currentCorner[CENTER_Y1] == AREA_MAX && map.currentCorner[CENTER_Y2]
	                                           == AREA_MIN
	                                           && map.currentMap.y == map.currentBoundaryMap1.y && map.currentMap.y <=
	                                           map.currentBoundaryMap2.y,
	                                           //境界線交差時の特殊条件
	                                           map.currentCorner[LEFT] == AREA_MAX && map.currentCorner[RIGHT] ==
	                                           AREA_MIN
	                                           && map.currentCorner[UP] == AREA_MAX && map.currentCorner[DOWN] ==
	                                           AREA_MIN
	                                           && map.currentMap.x == map.currentBoundaryMap1.x && map.currentMap.y >
	                                           map.currentBoundaryMap1.y
	                                           && map.currentMap.x < map.currentBoundaryMap2.x && map.currentMap.y ==
	                                           map.currentBoundaryMap2.y
                                           } {
}

MapCollision::~MapCollision() {
}

void MapCollision::update() {

	/* 12ヵ所で衝突判定を行う */
	collisionDetectionLeftUp(); //左上
	collisionDetectionLeftDown(); //右上
	collisionDetectionRightUp(); //左下
	collisionDetectionRightDown(); //右下

	collisionDetectionCenterLeft1(); //中央左1
	collisionDetectionCenterLeft2(); //中央左2
	collisionDetectionCenterRight1(); //中央右1
	collisionDetectionCenterRight2(); //中央右2

	collisionDetectionCenterUp1(); //中央上1
	collisionDetectionCenterUp2(); //中央上2
	collisionDetectionCenterDown1(); //中央下1
	collisionDetectionCenterDown2(); //中央下2
}

/// <summary>
/// 左上の衝突判定
/// </summary>
void MapCollision::collisionDetectionLeftUp() {
	if (boundaryCriteria[CROSS])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_TOP_LEFT, LEFT, UP)) ? true : false;
	else if (boundaryCriteria[LEFT])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, UP)) ? true : false;
	else if (boundaryCriteria[UP])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_TOP_CENTRAL, LEFT, UP)) ? true : false;
	else
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_CENTRAL, LEFT, UP)) ? true : false;
}

/// <summary>
/// 右上の衝突判定
/// </summary>
void MapCollision::collisionDetectionRightUp() {
	if (boundaryCriteria[CROSS] || boundaryCriteria[UP])
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_TOP_CENTRAL, RIGHT, UP)) ? true : false;
	else if (boundaryCriteria[RIGHT])
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, UP)) ? true : false;
	else
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_CENTRAL, RIGHT, UP)) ? true : false;
}

/// <summary>
/// 左下の衝突判定
/// </summary>
void MapCollision::collisionDetectionLeftDown() {
	if (boundaryCriteria[LEFT] || boundaryCriteria[CROSS])
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, DOWN)) ? true : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_BOTTOM_CENTRAL, LEFT, DOWN)) ? true : false;
	else
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_CENTRAL, LEFT, DOWN)) ? true : false;
}

/// <summary>
/// 右下の衝突判定
/// </summary>
void MapCollision::collisionDetectionRightDown() {
	if (boundaryCriteria[RIGHT])
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, DOWN)) ? true : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_BOTTOM_CENTRAL, RIGHT, DOWN)) ? true : false;
	else
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_CENTRAL, RIGHT, DOWN)) ? true : false;
}

/// <summary>
/// 左中央1の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterLeft1() {
	if (boundaryCriteria[CENTER_Y1])
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_TOP_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
	else if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
	else
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
}

/// <summary>
/// 左中央2の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterLeft2() {
	if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT2] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, CENTER_Y2)) ? true : false;
	else
		collisionFlag[CENTER_LEFT2] = (collisionDetection(MAP_CENTRAL, LEFT, CENTER_Y2)) ? true : false;
}

/// <summary>
/// 右中央1の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterRight1() {
	if (boundaryCriteria[CENTER_Y1])
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_TOP_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
	else if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
	else
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
}

/// <summary>
/// 右中央2の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterRight2() {
	if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT2] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, CENTER_Y2)) ? true : false;
	else
		collisionFlag[CENTER_RIGHT2] = (collisionDetection(MAP_CENTRAL, RIGHT, CENTER_Y2)) ? true : false;
}

/// <summary>
/// 上中央1の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterUp1() {
	if (boundaryCriteria[CENTER_X1])
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_LEFT_CENTRAL, CENTER_X1, UP)) ? true : false;
	else if (boundaryCriteria[UP])
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_TOP_CENTRAL, CENTER_X1, UP)) ? true : false;
	else
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_CENTRAL, CENTER_X1, UP)) ? true : false;
}

/// <summary>
/// 上中央2の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterUp2() {
	if (boundaryCriteria[CENTER_X2])
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_RIGHT_CENTRAL, CENTER_X2, UP)) ? true : false;
	else if (boundaryCriteria[UP])
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_TOP_CENTRAL, CENTER_X2, UP)) ? true : false;
	else
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_CENTRAL, CENTER_X2, UP)) ? true : false;
}

/// <summary>
/// 下中央1の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterDown1() {
	if (boundaryCriteria[CENTER_X1])
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_LEFT_CENTRAL, CENTER_X1, DOWN)) ? true : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_BOTTOM_CENTRAL, CENTER_X1, DOWN)) ? true : false;
	else
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_CENTRAL, CENTER_X1, DOWN)) ? true : false;
}

/// <summary>
/// 下中央2の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterDown2() {
	if (boundaryCriteria[CENTER_X2])
		collisionFlag[CENTER_DOWN2] = (collisionDetection(MAP_RIGHT_CENTRAL, CENTER_X2, DOWN)) ? true : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[CENTER_DOWN2] = (collisionDetection(MAP_BOTTOM_CENTRAL, CENTER_X2, DOWN)) ? true : false;
	else
		collisionFlag[CENTER_DOWN2] = (collisionDetection(MAP_CENTRAL, CENTER_X2, DOWN)) ? true : false;
}

/// <summary>
/// 判定を行うマップとそのマップの座標の組み合わせで衝突判定をとる
/// 結果をbool値で返す
/// </summary>
/// <param name="dirXY">判定を行うマップ名</param>
/// <param name="dirX">判定対象のx座標</param>
/// <param name="dirY">判定対象のy座標</param>
bool MapCollision::collisionDetection(const int& dirXY, const int& dirX, const int& dirY) {
	switch (dirXY) {
	case MAP_TOP_LEFT:
		return map.mapTopLeft[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_TOP_CENTRAL:
		return map.mapTopCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_TOP_RIGHT:
		return map.mapTopRight[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_LEFT_CENTRAL:
		return map.mapLeftCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_CENTRAL:
		return map.mapCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_RIGHT_CENTRAL:
		return map.mapRightCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_BOTTOM_LEFT:
		return map.mapBottomLeft[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_BOTTOM_CENTRAL:
		return map.mapBottomCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_BOTTOM_RIGHT:
		return map.mapBottomRight[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	default:
		return false;
	}
}

int MapCollision::collisionRange() {
	return SEA;
}


//左上（3点）方向の衝突判定
bool MapCollision::leftUpCollisionFlag() {
	return collisionFlag[LEFT_UP] && collisionFlag[CENTER_UP1] && collisionFlag[CENTER_LEFT1];
}

//右上（3点）方向の衝突判定
bool MapCollision::rightUpCollisionFlag() {
	return collisionFlag[RIGHT_UP] && collisionFlag[CENTER_UP2] && collisionFlag[CENTER_RIGHT1];
}

//左下（3点）方向の衝突判定
bool MapCollision::leftDownCollisionFlag() {
	return collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_DOWN1] && collisionFlag[CENTER_LEFT2];
}

//右下（3点）方向の衝突判定
bool MapCollision::rightDownCollisionFlag() {
	return collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_DOWN2] && collisionFlag[CENTER_RIGHT2];
}

//--- 4方向（上下左右）の衝突判定の結果を返す ---//
//左方向
bool MapCollision::leftCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_LEFT1])
		|| (collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_LEFT2])
		|| (collisionFlag[CENTER_LEFT1] && collisionFlag[CENTER_LEFT2])
		|| leftUpCollisionFlag()
		|| leftDownCollisionFlag());
}

//右方向
bool MapCollision::rightCollisionFlag() {
	return ((collisionFlag[RIGHT_UP] && collisionFlag[CENTER_RIGHT1])
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_RIGHT2])
		|| (collisionFlag[CENTER_RIGHT1] && collisionFlag[CENTER_RIGHT2])
		|| rightUpCollisionFlag()
		|| rightDownCollisionFlag());
}

//上方向
bool MapCollision::upCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_UP1])
		|| (collisionFlag[RIGHT_UP] && collisionFlag[CENTER_UP2])
		|| (collisionFlag[CENTER_UP1] && collisionFlag[CENTER_UP2])
		|| leftUpCollisionFlag()
		|| rightUpCollisionFlag());
}

//下方向
bool MapCollision::downCollisionFlag() {
	return ((collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_DOWN1])
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_DOWN2])
		|| (collisionFlag[CENTER_DOWN1] && collisionFlag[CENTER_DOWN2])
		|| leftDownCollisionFlag()
		|| rightDownCollisionFlag());
}

//----------------------------------------//
