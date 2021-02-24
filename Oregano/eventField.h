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
	vector<bool> accessoryFlag; //アクセサリーフラグ
	vector<bool> jewelFlag; //ジュエルフラグ
	vector<bool> mineralFlag; //鉱物フラグ

	bool actionFlagX; //アクションフラグ

	const vector<int> coinQuantity; //コイン量

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
	vector<int> coin; //コイン情報格納用
	vector<int> item; //アイテム情報格納用
	vector<int> accessory; //アクセサリー情報格納用
	vector<int> jewel; //ジュエル情報格納用
	vector<int> mineral; //鉱物情報格納用

	EventField(Input& input, EventBase& event, Player& player);
	~EventField();

	void update();


};
