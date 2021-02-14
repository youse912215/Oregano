#include "eventBase.h"

int EventBase::gameScene = GAME_SCENE;

EventBase::EventBase(int graph) : MapDraw(graph) {
}

/// <summary>
/// �v���C���[��x�܂���y�̒��S���W���擾
/// </summary>
/// <param name="center">x�܂���y</param>
int EventBase::centralPlayerPosition(int center) {
	if (center == MAP_X) {
		return (mapX / BLOCK_SIZE) % 25;
	}
	return ((mapY - 16) / BLOCK_SIZE) % 25;
}

/// <summary>
/// ���݂̃}�b�v���W���擾
/// </summary>
/// <param name="current">x�܂���y</param>
int EventBase::currentMapPosition(int current) {
	if (current == MAP_X)
		return mapX / (BLOCK_SIZE * AREA_WIDTH);
	return mapY / (BLOCK_SIZE * AREA_HEIGHT);
}

/// <summary>
/// �C�x���g������������W�̐^�U��Ԃ�
/// </summary>
/// <param name="mapX">�}�b�vx���W</param>
/// <param name="mapY">�}�b�vy���W</param>
/// <param name="cX">���݂̃v���C���[�̒��Sx���W</param>
/// <param name="cY">���݂̃v���C���[�̒��Sy���W</param>
/// <returns></returns>
bool EventBase::getEventCoordinate(const int& mapX, const int& mapY, const int& cX, const int& cY) {
	return (currentMapPosition(MAP_X) == mapX)
		&& (currentMapPosition(MAP_Y) == mapY)
		&& (centralPlayerPosition(MAP_X) == cX)
		&& (centralPlayerPosition(MAP_Y) == cY);
}
