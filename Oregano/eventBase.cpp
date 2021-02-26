#include "eventBase.h"
#include "constant.h"
#include "DxLib.h"

int EventBase::gameScene = TITLE_SCENE;
bool EventBase::night = false;

EventBase::EventBase(int graph) : MapDraw(graph) {
	gameTime = GAME_HOUR * 19; //�������Ԃ�12��
}

/// <summary>
/// ��̏�Ԃ�ύX(4������20���܂ł͓����Ƃ��āAfalse��Ԃɂ���)
/// </summary>
void EventBase::changeTime() {
	night = (gameTime >= GAME_HOUR * 4 && gameTime <= GAME_HOUR * 20) ? false : true;
}

/// <summary>
/// �Q�[�����ԋN��
/// </summary>
void EventBase::moveGameTime() {
	gameTime = gameTime <= GAME_HOUR * 24 ? ++gameTime : 0; //24���ɂȂ�����A0���ɕύX
}

/// <summary>
/// �v���C���[��x�܂���y�̒��S���W���擾
/// </summary>
/// <param name="center">x�܂���y</param>
int EventBase::centralPlayerPosition(int center) {
	if (center == POSITION_X) {
		return (mapX / BLOCK_SIZE) % AREA_WIDTH;
	}
	return ((mapY - BLOCK_SIZE / 4) / BLOCK_SIZE) % AREA_HEIGHT;
}

/// <summary>
/// ���݂̃}�b�v���W���擾
/// </summary>
/// <param name="current">x�܂���y</param>
int EventBase::currentMapPosition(int current) {
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
	return (currentMapPosition(POSITION_X) == mapX)
		&& (currentMapPosition(POSITION_Y) == mapY)
		&& (centralPlayerPosition(POSITION_X) == cX)
		&& (centralPlayerPosition(POSITION_Y) == cY);
}

void EventBase::update() {
	moveGameTime(); //�Q�[�����ԋN��
	changeTime(); //��̏�Ԃ�ύX

	DrawFormatString(WIN_WIDTH - 300, WIN_HEIGHT - 15, GetColor(255, 0, 0), "TIME:%d, ��:%d",
	                 gameTime, night, false);
}
