#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"
#include <vector>

using namespace std;

//プレイヤー
class Player {
private:
	Input& input;
	DataSource& source;
	Vec2 knifePosition;

	vector<int> cooldown; //アクションのクールダウン
	vector<bool> cooldownFlag; //クールダウンのフラグ

	void draw(); //描画処理

	void actionCommand(); //アクションコマンドの処理

	void knifePositionSet(); //ナイフのポジジョンセット
	void knifePositionReset(); //ナイフのポジジョンリセット
	void accelKnife(); //ナイフの加速
	void knifeUpdate(); //ナイフの更新処理
	bool deleteKnife(); //ナイフの削除条件


public:
	Vec2 pos;
	Vec2 center;

	Vec2 knifePos;
	Vec2 knifeCenter;

	bool knife;
	bool rotatingSlash;

	vector<int> status;
	vector<int> possessionItem;
	vector<int> possessionAccessory;
	vector<int> possessionJewel;
	vector<int> possessionMineral;

	Player(Input& input, DataSource& source);
	~Player();

	void update();
};
