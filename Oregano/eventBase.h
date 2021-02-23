#pragma once
#include "mapDraw.h"

class EventBase : public MapDraw {
private:
	int gameTime; //�Q�[������

	void changeTime(); //��̏�Ԃ�ύX
	void moveGameTime();


public:
	static int gameScene; //�Q�[���V�[��
	static bool night; //true�Ȃ��

	EventBase(int graph = 0); //�R���X�g���N�^

	int centralPlayerPosition(int center); //���݂̃v���C���[�̒������W�擾
	int currentMapPosition(int current); //���݂̃}�b�v���W���擾

	bool getEventCoordinate(const int& mapX, const int& mapY, const int& cX, const int& cY); //�C�x���g���W�̐^�U

	void update(); //�X�V����
};
