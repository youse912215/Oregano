#pragma once
#include "inputProcess.h"
#include "eventBase.h"
#include "player.h"
#include <vector>

using namespace std;

class EventField {
private:
	Input& input; //入力クラスから
	EventBase& event; //イベントクラスから
	Player& player; //プレイヤークラスから


	void getFieldItem(); //フィールド上でのアイテム入手

	int directionSignX(const int& direction); //
	int directionSignY(const int& direction);
	int coinQuantity(const int& coinType);
	int coinType(const int& coinType);
	int directionReverse(const int& direction);

	vector<bool> coinFlag; //コインフラグ
	bool eventFlag; //イベントフラグ

public:
	vector<int> coin; //コイン情報格納用

	EventField(Input& input, EventBase& event, Player& player);
	~EventField();

	void update();


};
