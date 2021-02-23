#pragma once
#include "mapDraw.h"

class EventBase : public MapDraw {
private:


public:
	int centralPlayerPosition(int center); //���݂̃v���C���[�̒������W�擾
	int currentMapPosition(int current); //���݂̃}�b�v���W���擾
	static int gameScene; //�Q�[���V�[��
	static int gameTime; //�Q�[������

	EventBase(int graph = 0);
	bool getEventCoordinate(const int& mapX, const int& mapY, const int& cX, const int& cY); //�C�x���g���W�̐^�U
};
