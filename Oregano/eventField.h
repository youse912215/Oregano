#pragma once
#include "inputProcess.h"
#include "eventBase.h"
#include "player.h"
#include <vector>

using namespace std;

class EventField {
private:
	Input& input; //���̓N���X����
	EventBase& event; //�C�x���g�N���X����
	Player& player; //�v���C���[�N���X����


	void getFieldItem(); //�t�B�[���h��ł̃A�C�e������

	int directionSignX(const int& direction); //
	int directionSignY(const int& direction);
	int coinQuantity(const int& coinType);
	int coinType(const int& coinType);
	int directionReverse(const int& direction);

	vector<bool> coinFlag; //�R�C���t���O
	bool eventFlag; //�C�x���g�t���O

public:
	vector<int> coin; //�R�C�����i�[�p

	EventField(Input& input, EventBase& event, Player& player);
	~EventField();

	void update();


};
