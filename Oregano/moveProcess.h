#pragma once
#include "mapDraw.h"
#include "mapCollision.h"

class MoveProcess {
private:
	bool mapCondition(MapDraw& draw, const int& mapInfo); //����
	int movingDistance(MapDraw& draw); //�ړ�����

public:
	void left(MapCollision& collision, MapDraw& draw); //���ړ�
	void right(MapCollision& collision, MapDraw& draw); //�E�ړ�
	void up(MapCollision& collision, MapDraw& draw); //��ړ�
	void down(MapCollision& collision, MapDraw& draw); //���ړ�


};
