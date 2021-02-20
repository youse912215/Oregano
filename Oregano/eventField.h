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
	int coinQuantityDecision(const int& coinType);
	int coinTypeDecision(const int& coinType);
	int directionReverse(const int& direction);

	vector<bool> coinFlag; //コインフラグ
	bool eventFlag; //イベントフラグ

	const vector<int> coinQuantity;

public:
	vector<int> coin; //コイン情報格納用

	EventField(Input& input, EventBase& event, Player& player);
	~EventField();

	void update();


};
