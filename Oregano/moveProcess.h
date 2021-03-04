#pragma once
#include "mapDraw.h"
#include "mapCollision.h"

class MoveProcess {
private:
	bool collisionDirectionLeft(MapCollision& collision); //���̏Փ˔���
	bool collisionDirectionRight(MapCollision& collision); //�E�̏Փ˔���
	bool collisionDirectionUp(MapCollision& collision); //��̏Փ˔���
	bool collisionDirectionDown(MapCollision& collision); //���̏Փ˔���

	int movingDistance(MapDraw& draw); //�ړ�����
	int invert(); //�����𔽓]������

public:
	bool mapCondition(MapDraw& draw, const int& mapInfo); //�}�b�v����

	int changeDirection(const int& dir); //�����̏���؂�ւ���

	void left(MapCollision& collision, MapDraw& draw); //���ړ�
	void right(MapCollision& collision, MapDraw& draw); //�E�ړ�
	void up(MapCollision& collision, MapDraw& draw); //��ړ�
	void down(MapCollision& collision, MapDraw& draw); //���ړ�
};
