#include "moveProcess.h"

bool MoveProcess::mapCondition(MapDraw& draw, const int& mapInfo) {
	return draw.mapCentral[draw.blockArea.y][draw.blockArea.x] == mapInfo;
}

/// <summary>
/// ���݂̃}�b�v�̏��ɂ���āA�ړ�������Ԃ�
/// </summary>
/// <param name="draw">�}�b�v�`��N���X</param>
/// <param name="mapInfo">�}�b�v���</param>
int MoveProcess::movingDistance(MapDraw& draw) {
	//�󐣂̂Ƃ�
	if (mapCondition(draw, SHALLOW))
		return MOVING_DISTANCE / 2; //�ړ�������1/2
	//�����̂Ƃ�
	if (mapCondition(draw, SWAMP))
		return MOVING_DISTANCE / 4; //�ړ�������1/4
	//����ȊO
	return MOVING_DISTANCE; //�ʏ�̈ړ�����
}

/// <summary>
/// ���ړ�
/// </summary>
void MoveProcess::left(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapX -= movingDistance(draw);
	if (collision.leftCollisionFlag()) MapDraw::mapX += movingDistance(draw);
}

/// <summary>
/// �E�ړ�
/// </summary>
void MoveProcess::right(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapX += movingDistance(draw);
	if (collision.rightCollisionFlag()) MapDraw::mapX -= movingDistance(draw);
}

/// <summary>
/// ��ړ�
/// </summary>
void MoveProcess::up(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapY -= movingDistance(draw);
	if (collision.upCollisionFlag()) MapDraw::mapY += movingDistance(draw);
}

/// <summary>
/// ���ړ�
/// </summary>
void MoveProcess::down(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapY += movingDistance(draw);
	if (collision.downCollisionFlag()) MapDraw::mapY -= movingDistance(draw);
}
