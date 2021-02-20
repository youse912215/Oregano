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

	vector<bool> coinFlag; //�R�C���t���O
	vector<bool> itemFlag; //�A�C�e���t���O
	bool actionFlagX; //�A�N�V�����t���O

	const vector<int> coinQuantity; //�R�C����

	void getFieldItem(vector<int>& eventName, vector<bool>& eventFlag);
	void fieldAction();

	int directionSignX(const int& direction); //
	int directionSignY(const int& direction);
	int coinQuantityDecision(const int& coinType);
	int coinTypeDecision(const int& coinType);
	int directionReverse(const int& direction);

public:
	vector<int> coin; //�R�C�����i�[�p
	vector<int> item; //�A�C�e�����i�[�p

	EventField(Input& input, EventBase& event, Player& player);
	~EventField();

	void update();


};
