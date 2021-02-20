#pragma once
#include "inputProcess.h"
#include "eventBase.h"
#include "player.h"

class EventField {
private:
	Input& input; //���͏�������
	EventBase& event; //�C�x���g����
	Player& player; //�v���C���[����

	int coin; //�R�C��

	void getFieldItem(); //�t�B�[���h��ł̃A�C�e������

public:
	bool eventFlag; //�C�x���g�t���O


	EventField(Input& input, EventBase& event, Player& player);
	~EventField();

	void update();


};
