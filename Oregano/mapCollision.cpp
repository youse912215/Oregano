#include "mapCollision.h"
#include "constant.h"
#include "mapDraw.h"
#include "DxLib.h"

MapCollision::MapCollision(MapDraw& map) : map(map) {
}

void MapCollision::update() {

}

//����i3�_�j�����̏Փ˔���
bool MapCollision::leftUpCollisionFlag() {
	return map.collisionFlag[LEFT_UP] && map.collisionFlag[CENTER_UP1] && map.collisionFlag[CENTER_LEFT1];
}

//�E��i3�_�j�����̏Փ˔���
bool MapCollision::rightUpCollisionFlag() {
	return map.collisionFlag[RIGHT_UP] && map.collisionFlag[CENTER_UP2] && map.collisionFlag[CENTER_RIGHT1];
}

//�����i3�_�j�����̏Փ˔���
bool MapCollision::leftDownCollisionFlag() {
	return map.collisionFlag[LEFT_DOWN] && map.collisionFlag[CENTER_DOWN1] && map.collisionFlag[CENTER_LEFT2];
}

//�E���i3�_�j�����̏Փ˔���
bool MapCollision::rightDownCollisionFlag() {
	return map.collisionFlag[RIGHT_DOWN] && map.collisionFlag[CENTER_DOWN2] && map.collisionFlag[CENTER_RIGHT2];
}

//--- 4�����i�㉺���E�j�̏Փ˔���̌��ʂ�Ԃ� ---//
//������
bool MapCollision::leftCollisionFlag() {
	return ((map.collisionFlag[LEFT_UP] && map.collisionFlag[CENTER_LEFT1])
		|| (map.collisionFlag[LEFT_DOWN] && map.collisionFlag[CENTER_LEFT2])
		|| (map.collisionFlag[CENTER_LEFT1] && map.collisionFlag[CENTER_LEFT2])
		|| leftUpCollisionFlag()
		|| leftDownCollisionFlag());
}

//�E����
bool MapCollision::rightCollisionFlag() {
	return ((map.collisionFlag[RIGHT_UP] && map.collisionFlag[CENTER_RIGHT1])
		|| (map.collisionFlag[RIGHT_DOWN] && map.collisionFlag[CENTER_RIGHT2])
		|| (map.collisionFlag[CENTER_RIGHT1] && map.collisionFlag[CENTER_RIGHT2])
		|| rightUpCollisionFlag()
		|| rightDownCollisionFlag());
}

//�����
bool MapCollision::upCollisionFlag() {
	return ((map.collisionFlag[LEFT_UP] && map.collisionFlag[CENTER_UP1])
		|| (map.collisionFlag[RIGHT_UP] && map.collisionFlag[CENTER_UP2])
		|| (map.collisionFlag[CENTER_UP1] && map.collisionFlag[CENTER_UP2])
		|| leftUpCollisionFlag()
		|| rightUpCollisionFlag());
}

//������
bool MapCollision::downCollisionFlag() {
	return ((map.collisionFlag[LEFT_DOWN] && map.collisionFlag[CENTER_DOWN1])
		|| (map.collisionFlag[RIGHT_DOWN] && map.collisionFlag[CENTER_DOWN2])
		|| (map.collisionFlag[CENTER_DOWN1] && map.collisionFlag[CENTER_DOWN2])
		|| leftDownCollisionFlag()
		|| rightDownCollisionFlag());
}

//----------------------------------------//
