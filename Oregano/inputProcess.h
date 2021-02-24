#pragma once
#include "DxLib.h"
#include "mapCollision.h"
#include <vector>

using namespace std;

class Input {
private:
	static char oldkeys[256]; //�O�̃L�[���͂̏��
	static char keys[256]; //�L�[���͂̏��

	int oldPad; //�O�̃L�[���͂̏��
	int pad; //�L�[���͂̏��


	bool mode;

	vector<bool> padNum;
	vector<bool> inputButton;

	bool getInputButton(const int& buttonName);

public:
	static int add;

	vector<bool> buttonFlag;
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;

	int moveDirection; //�����Ă���ړ�����

	Input();
	void keyboardInformation();
	void padsInformation();
	void inputModeChange();
	void moveProcess(MapCollision& collision);
	void eventProcess();
	void endProcess();
	void update();
};
