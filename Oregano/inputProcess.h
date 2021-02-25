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

	bool mode; //入力モード

	vector<bool> padNum; //ジョイパッド番号
	vector<bool> inputButton; //入力ボタン

	bool getInputButton(const int& buttonName); //ボタン入力を返す

public:
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;

	int moveDirection; //今見ている移動方向

	vector<bool> buttonFlag; //ボタンフラグ

	Input(); //コンストラクタ

	void keyboardInformation(); //キーボード情報
	void padsInformation(); //ジョイパッド情報
	void inputModeChange(); //キーボードとジョイパッドを切り替える
	void moveProcess(MapCollision& collision); //入力処理
	void eventProcess(); //ボタン入力処理
	void endProcess(); //終了処理
	void update(); //更新処理
};
