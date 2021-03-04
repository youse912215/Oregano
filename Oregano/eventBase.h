#pragma once
#include "mapDraw.h"

class EventBase : public MapDraw {
private:

public:
	static int gameScene; //�Q�[���V�[��

	EventBase();

	int blockAreaPos(int center); //���݂̃v���C���[�̒������W�擾
	int currentMapPos(int current); //���݂̃}�b�v���W���擾

	bool getEventCoordinate(const int& mapX, const int& mapY, const int& cX, const int& cY); //�C�x���g���W�̐^�U

	void update(); //�X�V����
};
