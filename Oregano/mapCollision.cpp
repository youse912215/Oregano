#include "mapCollision.h"
#include "constant.h"
#include "mapDraw.h"

MapCollision::MapCollision(MapDraw& map) : map(map), collisionFlag(12),
                                           boundaryCriteria(9) {
}

MapCollision::~MapCollision() {

}

/// <summary>
/// ������
/// </summary>
void MapCollision::initialize() {
	boundaryCriteria = {
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
		};
}

/// <summary>
/// �X�V����
/// </summary>
void MapCollision::update() {

	initialize(); //������

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
	//�}�b�v�̋��E���������_�t�߂̂Ƃ�
	if (boundaryCriteria[CROSS])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_TOP_LEFT, LEFT, UP)) ? true : false;
		//�}�b�v�̋��E�������̂Ƃ�
	else if (boundaryCriteria[LEFT])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, UP)) ? true : false;
		//�}�b�v�̋��E������̂Ƃ�
	else if (boundaryCriteria[UP])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_TOP_CENTRAL, LEFT, UP)) ? true : false;
		//����ȊO
	else
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_CENTRAL, LEFT, UP)) ? true : false;
}

/// <summary>
/// �E��̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionRightUp() {
	//�}�b�v�̋��E���������_�t�߂̂Ƃ��܂��́A��̂Ƃ�
	if (boundaryCriteria[CROSS] || boundaryCriteria[UP])
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_TOP_CENTRAL, RIGHT, UP)) ? true : false;
		//�}�b�v�̋��E�����E�̂Ƃ�
	else if (boundaryCriteria[RIGHT])
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, UP)) ? true : false;
		//����ȊO
	else
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_CENTRAL, RIGHT, UP)) ? true : false;
}

/// <summary>
/// �����̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionLeftDown() {
	//�}�b�v�̋��E���������_�t�߂̂Ƃ��܂��́A���̂Ƃ�
	if (boundaryCriteria[LEFT] || boundaryCriteria[CROSS])
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, DOWN)) ? true : false;
		//�}�b�v�̋��E�������̂Ƃ�
	else if (boundaryCriteria[DOWN])
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_BOTTOM_CENTRAL, LEFT, DOWN)) ? true : false;
		//����ȊO
	else
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_CENTRAL, LEFT, DOWN)) ? true : false;
}

/// <summary>
/// �E���̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionRightDown() {
	//�}�b�v�̋��E�����E�̂Ƃ�
	if (boundaryCriteria[RIGHT])
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, DOWN)) ? true : false;
		//�}�b�v�̋��E�������̂Ƃ�
	else if (boundaryCriteria[DOWN])
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_BOTTOM_CENTRAL, RIGHT, DOWN)) ? true : false;
		//����ȊO
	else
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_CENTRAL, RIGHT, DOWN)) ? true : false;
}

/// <summary>
/// ������1�̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionCenterLeft1() {
	//�}�b�v�̋��E����������̂Ƃ�
	if (boundaryCriteria[CENTER_Y1])
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_TOP_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
		//�}�b�v�̋��E�������̂Ƃ�
	else if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
		//����ȊO
	else
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
}

/// <summary>
/// ������2�̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionCenterLeft2() {
	//�}�b�v�̋��E�������̂Ƃ�
	if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT2] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, CENTER_Y2)) ? true : false;
		//����ȊO
	else
		collisionFlag[CENTER_LEFT2] = (collisionDetection(MAP_CENTRAL, LEFT, CENTER_Y2)) ? true : false;
}

/// <summary>
/// �E����1�̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionCenterRight1() {
	//�}�b�v�̋��E����������̂Ƃ�
	if (boundaryCriteria[CENTER_Y1])
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_TOP_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
		//�}�b�v�̋��E�����E�̂Ƃ�
	else if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
		//����ȊO
	else
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
}

/// <summary>
/// �E����2�̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionCenterRight2() {
	//�}�b�v�̋��E�����E�̂Ƃ�
	if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT2] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, CENTER_Y2)) ? true : false;
		//����ȊO
	else
		collisionFlag[CENTER_RIGHT2] = (collisionDetection(MAP_CENTRAL, RIGHT, CENTER_Y2)) ? true : false;
}

/// <summary>
/// �㒆��1�̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionCenterUp1() {
	//�}�b�v�̋��E�����������̂Ƃ�
	if (boundaryCriteria[CENTER_X1])
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_LEFT_CENTRAL, CENTER_X1, UP)) ? true : false;
		//�}�b�v�̋��E������̂Ƃ�
	else if (boundaryCriteria[UP])
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_TOP_CENTRAL, CENTER_X1, UP)) ? true : false;
		//����ȊO
	else
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_CENTRAL, CENTER_X1, UP)) ? true : false;
}

/// <summary>
/// �㒆��2�̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionCenterUp2() {
	//�}�b�v�̋��E���������E�̂Ƃ�
	if (boundaryCriteria[CENTER_X2])
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_RIGHT_CENTRAL, CENTER_X2, UP)) ? true : false;
		//�}�b�v�̋��E������̂Ƃ�
	else if (boundaryCriteria[UP])
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_TOP_CENTRAL, CENTER_X2, UP)) ? true : false;
		//����ȊO
	else
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_CENTRAL, CENTER_X2, UP)) ? true : false;
}

/// <summary>
/// ������1�̏Փ˔���
/// </summary>
void MapCollision::collisionDetectionCenterDown1() {
	//�}�b�v�̋��E�����������̂Ƃ�
	if (boundaryCriteria[CENTER_X1])
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_LEFT_CENTRAL, CENTER_X1, DOWN)) ? true : false;
		//�}�b�v�̋��E�������̂Ƃ�
	else if (boundaryCriteria[DOWN])
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_BOTTOM_CENTRAL, CENTER_X1, DOWN)) ? true : false;
		//����ȊO
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
		//����ȊO
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

	/* ����ӏ���WALL(��)�Əd�Ȃ��Ă���Ȃ�true��Ԃ� */
	switch (dirXY) {
	case MAP_TOP_LEFT: //����}�b�v
		return map.mapTopLeft[map.currentCorner[dirY]][map.currentCorner[dirX]] >= WALL;
	case MAP_TOP_CENTRAL: //������}�b�v
		return map.mapTopCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= WALL;
	case MAP_TOP_RIGHT: //�E��}�b�v
		return map.mapTopRight[map.currentCorner[dirY]][map.currentCorner[dirX]] >= WALL;
	case MAP_LEFT_CENTRAL: //�������}�b�v
		return map.mapLeftCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= WALL;
	case MAP_CENTRAL: //�����}�b�v
		return map.mapCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= WALL;
	case MAP_RIGHT_CENTRAL: //�E�����}�b�v
		return map.mapRightCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= WALL;
	case MAP_BOTTOM_LEFT: //�����}�b�v
		return map.mapBottomLeft[map.currentCorner[dirY]][map.currentCorner[dirX]] >= WALL;
	case MAP_BOTTOM_CENTRAL: //�������}�b�v
		return map.mapBottomCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= WALL;
	case MAP_BOTTOM_RIGHT: //�E���}�b�v
		return map.mapBottomRight[map.currentCorner[dirY]][map.currentCorner[dirX]] >= WALL;
	default:
		return false; //����ȊO��false��Ԃ�
	}
}

//����i3�_�j�����̏Փ˔���
bool MapCollision::leftUpCollisionFlag() {
	//����A������1�i����ƒ�����̊ԁj�A������1�i����ƒ������̊ԁj
	return collisionFlag[LEFT_UP] && collisionFlag[CENTER_UP1] && collisionFlag[CENTER_LEFT1];
}

//�E��i3�_�j�����̏Փ˔���
bool MapCollision::rightUpCollisionFlag() {
	//�E��A������2�i�E��ƒ�����̊ԁj�A�����E1�i�E��ƒ����E�̊ԁj
	return collisionFlag[RIGHT_UP] && collisionFlag[CENTER_UP2] && collisionFlag[CENTER_RIGHT1];
}

//�����i3�_�j�����̏Փ˔���
bool MapCollision::leftDownCollisionFlag() {
	//�����A������1�i�����ƒ������̊ԁj�A������2�i�����ƒ������̊ԁj
	return collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_DOWN1] && collisionFlag[CENTER_LEFT2];
}

//�E���i3�_�j�����̏Փ˔���
bool MapCollision::rightDownCollisionFlag() {
	//�E���A������2�i�E���ƒ������̊ԁj�A�����E2�i�E���ƒ����E�̊ԁj
	return collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_DOWN2] && collisionFlag[CENTER_RIGHT2];
}

//--- 4�����i�㉺���E�j�̏Փ˔���̌��ʂ�Ԃ� ---//
//������
bool MapCollision::leftCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_LEFT1]) //����ƒ�����1
		|| (collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_LEFT2]) //�����ƒ�����2
		|| (collisionFlag[CENTER_LEFT1] && collisionFlag[CENTER_LEFT2]) //������1�ƒ�����2
		|| leftUpCollisionFlag() //����3�_
		|| leftDownCollisionFlag()); //����3�_
}

//�E����
bool MapCollision::rightCollisionFlag() {
	return ((collisionFlag[RIGHT_UP] && collisionFlag[CENTER_RIGHT1]) //�E��ƒ����E1
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_RIGHT2]) //�E���ƒ����E2
		|| (collisionFlag[CENTER_RIGHT1] && collisionFlag[CENTER_RIGHT2]) //�����E1�ƒ����E2
		|| rightUpCollisionFlag() //�E��3�_
		|| rightDownCollisionFlag()); //�E��3�_
}

//�����
bool MapCollision::upCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_UP1]) //����ƒ�����1
		|| (collisionFlag[RIGHT_UP] && collisionFlag[CENTER_UP2]) //�E��ƒ�����2
		|| (collisionFlag[CENTER_UP1] && collisionFlag[CENTER_UP2]) //������1�ƒ�����2
		|| leftUpCollisionFlag() //����3�_
		|| rightUpCollisionFlag()); //�E��3�_
}

//������
bool MapCollision::downCollisionFlag() {
	return ((collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_DOWN1]) //�����ƒ�����1
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_DOWN2]) //�E���ƒ�����2
		|| (collisionFlag[CENTER_DOWN1] && collisionFlag[CENTER_DOWN2]) //������1�ƒ�����2
		|| leftDownCollisionFlag() //����3�_
		|| rightDownCollisionFlag()); //�E��3�_
}

//----------------------------------------//
