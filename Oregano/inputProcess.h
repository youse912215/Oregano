#pragma once
#include "DxLib.h"
#include "mapCollision.h"
#include <vector>

using namespace std;

class Input {
private:
	static char oldkeys[256]; //前のキー入力の状態
	static char keys[256]; //キー入力の状態

	int oldPad; //前のキー入力の状態
	int pad; //キー入力の状態


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

	int moveDirection; //今見ている移動方向

	Input();
	void keyboardInformation();
	void padsInformation();
	void inputModeChange();
	void moveProcess(MapCollision& collision);
	void eventProcess();
	void endProcess();
	void update();
};
