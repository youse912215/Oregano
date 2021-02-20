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
	int coinQuantityDecision(const int& coinType);
	int coinTypeDecision(const int& coinType);
	int directionReverse(const int& direction);

	vector<bool> coinFlag; //�R�C���t���O
	bool eventFlag; //�C�x���g�t���O

	const vector<int> coinQuantity;

public:
	vector<int> coin; //�R�C�����i�[�p

	EventField(Input& input, EventBase& event, Player& player);
	~EventField();

	void update();


};
