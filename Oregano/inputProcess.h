#pragma once
#include "DxLib.h"
#include "mapCollision.h"
#include "mapDraw.h"
#include "moveProcess.h"
#include <vector>

using namespace std;

class Input {
private:
	MoveProcess move_;

	static char oldkeys[256]; //前のキー入力の状態
	static char keys[256]; //キー入力の状態

	int oldPad; //前のキー入力の状態
	int pad; //キー入力の状態

	bool mode; //入力モード

	vector<bool> padNum; //ジョイパッド番号
	vector<bool> oldPadNum;
	vector<bool> inputButton; //入力ボタン

	bool getInputButton(const int& buttonName); //ボタン入力を返す

	void directionProcess(const int& dir); //方向処理
	void keyboardInformation(); //キーボード情報
	void padsInformation(); //ジョイパッド情報
	void inputModeChange(); //キーボードとジョイパッドを切り替える
	void eventProcess(); //ボタン入力処理
	void endProcess(); //終了処理

public:
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;

	vector<bool> buttonFlag; //ボタンフラグ
	vector<bool> STICK;
	bool anySTICK();

	int moveDirection; //今見ている移動方向

	Input(); //コンストラクタ

	void movement(MapCollision& collision, MapDraw& draw); //入力処理
	void update(); //更新処理
};
