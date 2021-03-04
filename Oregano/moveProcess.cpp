#include "moveProcess.h"
#include "playerState.h"

PlayerState state_;


bool MoveProcess::mapCondition(MapDraw& draw, const int& mapInfo) {
	return draw.mapCentral[draw.blockArea.y][draw.blockArea.x] == mapInfo;
}

bool MoveProcess::collisionDirectionLeft(MapCollision& collision) {
	if (!state_.stateAbnormal[CONFUSION])
		return collision.leftCollisionFlag();
	return collision.rightCollisionFlag();
}

bool MoveProcess::collisionDirectionRight(MapCollision& collision) {
	if (!state_.stateAbnormal[CONFUSION])
		return collision.rightCollisionFlag();
	return collision.leftCollisionFlag();
}

bool MoveProcess::collisionDirectionUp(MapCollision& collision) {
	if (!state_.stateAbnormal[CONFUSION])
		return collision.upCollisionFlag();
	return collision.downCollisionFlag();
}

bool MoveProcess::collisionDirectionDown(MapCollision& collision) {
	if (!state_.stateAbnormal[CONFUSION])
		return collision.downCollisionFlag();
	return collision.upCollisionFlag();
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
	if (mapCondition(draw, ICE))
		return MOVING_DISTANCE * 2; //�ړ�������2�{
	//����ȊO
	return MOVING_DISTANCE; //�ʏ�̈ړ�����
}

/// <summary>
/// �����𔽓]
/// </summary>
int MoveProcess::invert() {
	if (!state_.stateAbnormal[CONFUSION])
		return 1;
	return -1;
}

/// <summary>
/// �����̏���؂�ւ���
/// </summary>
/// <param name="dir">����</param>
int MoveProcess::changeDirection(const int& dir) {
	if (!state_.stateAbnormal[CONFUSION]) return dir;
	if (dir == LEFT) return RIGHT;
	if (dir == RIGHT) return LEFT;
	if (dir == UP) return DOWN;
	if (dir == DOWN) return UP;
	return 0;
}

/// <summary>
/// ���ړ�
/// </summary>
void MoveProcess::left(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapX -= movingDistance(draw) * invert(); //�ʏ펞
	if (collisionDirectionLeft(collision))
		MapDraw::mapX += movingDistance(draw) * invert(); //�Փˎ�
}

/// <summary>
/// �E�ړ�
/// </summary>
void MoveProcess::right(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapX += movingDistance(draw) * invert(); //�ʏ펞
	if (collisionDirectionRight(collision))
		MapDraw::mapX -= movingDistance(draw) * invert(); //�Փˎ�
}

/// <summary>
/// ��ړ�
/// </summary>
void MoveProcess::up(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapY -= movingDistance(draw) * invert(); //�ʏ펞
	if (collisionDirectionUp(collision))
		MapDraw::mapY += movingDistance(draw) * invert(); //�Փˎ�
}

/// <summary>
/// ���ړ�
/// </summary>
void MoveProcess::down(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapY += movingDistance(draw) * invert(); //�ʏ펞
	if (collisionDirectionDown(collision))
		MapDraw::mapY -= movingDistance(draw) * invert(); //�Փˎ�
}
