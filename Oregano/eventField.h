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
	vector<bool> accessoryFlag; //�A�N�Z�T���[�t���O
	vector<bool> jewelFlag; //�W���G���t���O
	vector<bool> mineralFlag; //�z���t���O

	bool actionFlagX; //�A�N�V�����t���O

	const vector<int> coinQuantity; //�R�C����

	void getFieldObject(vector<int>& objectName, vector<bool>& eventFlag, vector<int>& saveLocation);

	void fieldAction();
	void changeMenuScene();

	int directionSignX(const int& direction); //
	int directionSignY(const int& direction);
	int coinQuantityDecision(const int& coinType);
	int coinTypeDecision(const int& coinType);
	int directionReverse(const int& direction);

	void showEventState(vector<int>& objectName, vector<bool>& eventFlag);

public:
	vector<int> coin; //�R�C�����i�[�p
	vector<int> item; //�A�C�e�����i�[�p
	vector<int> accessory; //�A�N�Z�T���[���i�[�p
	vector<int> jewel; //�W���G�����i�[�p
	vector<int> mineral; //�z�����i�[�p

	EventField(Input& input, EventBase& event, Player& player);
	~EventField();

	void update();


};
