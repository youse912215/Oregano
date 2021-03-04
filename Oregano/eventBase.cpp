#include "eventBase.h"
#include "constant.h"
#include "DxLib.h"

int EventBase::gameScene = TITLE_SCENE;

EventBase::EventBase() {
}

/// <summary>
/// �v���C���[��x�܂���y�̒��S���W���擾
/// </summary>
/// <param name="center">x�܂���y</param>
int EventBase::blockAreaPos(int center) {
	if (center == POSITION_X) {
		return (mapX / BLOCK_SIZE) % AREA_WIDTH;
	}
	return ((mapY - QUARTER_BLOCK_SIZE) / BLOCK_SIZE) % AREA_HEIGHT;
}

/// <summary>
/// ���݂̃}�b�v���W���擾
/// </summary>
/// <param name="current">x�܂���y</param>
int EventBase::currentMapPos(int current) {
	if (current == POSITION_X)
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
	return (currentMapPos(POSITION_X) == mapX)
		&& (currentMapPos(POSITION_Y) == mapY)
		&& (blockAreaPos(POSITION_X) == cX)
		&& (blockAreaPos(POSITION_Y) == cY);
}

void EventBase::update() {
	DrawFormatString(100, 0, GetColor(255, 0, 0), "cx:%d, cy:%d,",
	                 blockAreaPos(POSITION_X), blockAreaPos(POSITION_Y), false);
}
