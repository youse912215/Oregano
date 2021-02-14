#pragma once
#include "inputProcess.h"
#include "eventBase.h"

class EventField {
private:
	Input& input; //���͏�������
	EventBase& event; //�C�x���g����

	int coin; //�R�C��

	void getFieldItem(); //�t�B�[���h��ł̃A�C�e������

public:
	bool eventFlag; //�C�x���g�t���O


	EventField(Input& input, EventBase& event);

	void update();


};
