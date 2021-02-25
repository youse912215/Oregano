#include "mapCollision.h"
#include "constant.h"
#include "mapDraw.h"
#include "eventBase.h"

MapCollision::MapCollision(MapDraw& map) : map(map), collisionFlag(12),
                                           boundaryCriteria{
	                                           //������
	                                           map.currentCorner[LEFT] == AREA_MAX && map.currentCorner[RIGHT] ==
	                                           AREA_MIN
	                                           && map.currentMap.x >= map.currentBoundaryMap1.x && map.currentMap.x ==
	                                           map.currentBoundaryMap2.x,
	                                           //�E����
	                                           map.currentCorner[LEFT] == AREA_MAX && map.currentCorner[RIGHT] ==
	                                           AREA_MIN
	                                           && map.currentMap.x == map.currentBoundaryMap1.x && map.currentMap.x <=
	                                           map.currentBoundaryMap2.x,
	                                           //�����
	                                           map.currentCorner[UP] == AREA_MAX && map.currentCorner[DOWN] == AREA_MIN
	                                           && map.currentMap.y >= map.currentBoundaryMap1.y && map.currentMap.y ==
	                                           map.currentBoundaryMap2.y,
	                                           //������
	                                           map.currentCorner[UP] == AREA_MAX && map.currentCorner[DOWN] == AREA_MIN
	                                           && map.currentMap.y == map.currentBoundaryMap1.y && map.currentMap.y <=
	                                           map.currentBoundaryMap2.y,
	                                           //������1����
	                                           map.currentCorner[CENTER_X1] == AREA_MAX && map.currentCorner[CENTER_X2]
	                                           == AREA_MIN
	                                           && map.currentMap.x >= map.currentBoundaryMap1.x && map.currentMap.x ==
	                                           map.currentBoundaryMap2.x,
	                                           //������2����
	                                           map.currentCorner[CENTER_X1] == AREA_MAX && map.currentCorner[CENTER_X2]
	                                           == AREA_MIN
	                                           && map.currentMap.x == map.currentBoundaryMap1.x && map.currentMap.x <=
	                                           map.currentBoundaryMap2.x,
	                                           //�����c1����
	                                           map.currentCorner[CENTER_Y1] == AREA_MAX && map.currentCorner[CENTER_Y2]
	                                           == AREA_MIN
	                                           && map.currentMap.y >= map.currentBoundaryMap1.y && map.currentMap.y ==
	                                           map.currentBoundaryMap2.y,
	                                           //�����c2����
	                                           map.currentCorner[CENTER_Y1] == AREA_MAX && map.currentCorner[CENTER_Y2]
	                                           == AREA_MIN
	                                           && map.currentMap.y == map.currentBoundaryMap1.y && map.currentMap.y <=
	                                           map.currentBoundaryMap2.y,
	                                           //���E���������̓������
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

	/* 12�����ŏՓ˔�����s�� */
	collisionDetectionLeftUp(); //����
	collisionDetectionLeftDown(); //�E��
	collisionDetectionRightUp(); //����
	collisionDetectionRightDown(); //�E��

	collisionDetectionCenterLeft1(); //������1
	collisionDetectionCenterLeft2(); //������2
	collisionDetectionCenterRight1(); //�����E1
	collisionDetectionCenterRight2(); //�����E2

	collisionDetectionCenterUp1(); //������1
	collisionDetectionCenterUp2(); //������2
	collisionDetectionCenterDown1(); //������1
	collisionDetectionCenterDown2(); //������2
}

/// <summary>
/// ����̏Փ˔���
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
/// �E��̏Փ˔���
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
/// �����̏Փ˔���
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
/// �E���̏Փ˔���
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
/// ������1�̏Փ˔���
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
/// ������2�̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionCenterLeft2() {
	if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT2] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, CENTER_Y2)) ? true : false;
	else
		collisionFlag[CENTER_LEFT2] = (collisionDetection(MAP_CENTRAL, LEFT, CENTER_Y2)) ? true : false;
}

/// <summary>
/// �E����1�̏Փ˔���
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
/// �E����2�̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionCenterRight2() {
	if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT2] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, CENTER_Y2)) ? true : false;
	else
		collisionFlag[CENTER_RIGHT2] = (collisionDetection(MAP_CENTRAL, RIGHT, CENTER_Y2)) ? true : false;
}

/// <summary>
/// �㒆��1�̏Փ˔���
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
/// �㒆��2�̏Փ˔���
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
/// ������1�̏Փ˔���
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
/// ������2�̏Փ˔���
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
/// ������s���}�b�v�Ƃ��̃}�b�v�̍��W�̑g�ݍ��킹�ŏՓ˔�����Ƃ�
/// ���ʂ�bool�l�ŕԂ�
/// </summary>
/// <param name="dirXY">������s���}�b�v��</param>
/// <param name="dirX">����Ώۂ�x���W</param>
/// <param name="dirY">����Ώۂ�y���W</param>
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


//����i3�_�j�����̏Փ˔���
bool MapCollision::leftUpCollisionFlag() {
	return collisionFlag[LEFT_UP] && collisionFlag[CENTER_UP1] && collisionFlag[CENTER_LEFT1];
}

//�E��i3�_�j�����̏Փ˔���
bool MapCollision::rightUpCollisionFlag() {
	return collisionFlag[RIGHT_UP] && collisionFlag[CENTER_UP2] && collisionFlag[CENTER_RIGHT1];
}

//�����i3�_�j�����̏Փ˔���
bool MapCollision::leftDownCollisionFlag() {
	return collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_DOWN1] && collisionFlag[CENTER_LEFT2];
}

//�E���i3�_�j�����̏Փ˔���
bool MapCollision::rightDownCollisionFlag() {
	return collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_DOWN2] && collisionFlag[CENTER_RIGHT2];
}

//--- 4�����i�㉺���E�j�̏Փ˔���̌��ʂ�Ԃ� ---//
//������
bool MapCollision::leftCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_LEFT1])
		|| (collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_LEFT2])
		|| (collisionFlag[CENTER_LEFT1] && collisionFlag[CENTER_LEFT2])
		|| leftUpCollisionFlag()
		|| leftDownCollisionFlag());
}

//�E����
bool MapCollision::rightCollisionFlag() {
	return ((collisionFlag[RIGHT_UP] && collisionFlag[CENTER_RIGHT1])
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_RIGHT2])
		|| (collisionFlag[CENTER_RIGHT1] && collisionFlag[CENTER_RIGHT2])
		|| rightUpCollisionFlag()
		|| rightDownCollisionFlag());
}

//�����
bool MapCollision::upCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_UP1])
		|| (collisionFlag[RIGHT_UP] && collisionFlag[CENTER_UP2])
		|| (collisionFlag[CENTER_UP1] && collisionFlag[CENTER_UP2])
		|| leftUpCollisionFlag()
		|| rightUpCollisionFlag());
}

//������
bool MapCollision::downCollisionFlag() {
	return ((collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_DOWN1])
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_DOWN2])
		|| (collisionFlag[CENTER_DOWN1] && collisionFlag[CENTER_DOWN2])
		|| leftDownCollisionFlag()
		|| rightDownCollisionFlag());
}

//----------------------------------------//
