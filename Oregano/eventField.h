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

	vector<bool> coinFlag; //コインフラグ
	vector<bool> itemFlag; //アイテムフラグ
	bool actionFlagX; //アクションフラグ

	const vector<int> coinQuantity; //コイン量

	void getFieldItem(vector<int>& eventName, vector<bool>& eventFlag);
	void fieldAction();

	int directionSignX(const int& direction); //
	int directionSignY(const int& direction);
	int coinQuantityDecision(const int& coinType);
	int coinTypeDecision(const int& coinType);
	int directionReverse(const int& direction);

public:
	vector<int> coin; //コイン情報格納用
	vector<int> item; //アイテム情報格納用

	EventField(Input& input, EventBase& event, Player& player);
	~EventField();

	void update();


};
