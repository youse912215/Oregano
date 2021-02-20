#pragma once
#include "inputProcess.h"
#include "eventBase.h"
#include "player.h"

class EventField {
private:
	Input& input; //入力処理から
	EventBase& event; //イベントから
	Player& player; //プレイヤーから

	int coin; //コイン

	void getFieldItem(); //フィールド上でのアイテム入手

public:
	bool eventFlag; //イベントフラグ


	EventField(Input& input, EventBase& event, Player& player);
	~EventField();

	void update();


};
