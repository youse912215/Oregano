#pragma once
#include "inputProcess.h"
#include "eventBase.h"

class EventField {
private:
	Input& input; //入力処理から
	EventBase& event; //イベントから

	int coin; //コイン

	void getFieldItem(); //フィールド上でのアイテム入手

public:
	bool eventFlag; //イベントフラグ


	EventField(Input& input, EventBase& event);

	void update();


};
