#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "mapDraw.h"
#include "dataSource.h"
#include <vector>

using namespace std;

//プレイヤー
class Player {
private:
	Input& input; //入力クラスから
	MapDraw& draw_;
	DataSource source; //データソースクラスから

	Vec2d pos; //プレイヤー座標

	vector<int> coin; //コイン（HP、攻撃の役割）
	vector<int> cooldown; //アクションのクールダウン
	vector<bool> cooldownFlag; //クールダウンのフラグ

	void draw(); //描画処理

	void actionCommand(); //アクションコマンドの処理


	void knifeUpdate(); //ナイフ更新処理
	void slashUpdate(); //刃更新処理
	void shieldUpdate(); //シールド更新処理
	void stateAbnormalUpdate(); //状態異常更新処理

	bool state(const int& num);
	bool cool(const int& num);

public:
	Vec2d center; //プレイヤーの中心座標
	Vec2d knifeCenter; //ナイフの中心座標
	Vec2d slashCenter; //刃の中心座標

	bool knife;
	bool slash;
	bool shield;
	bool elimination;

	void lostPlayerCoin(const int& attackPower); //コインの損失処理
	void addPlayerCoin(const int& attribute, const int& enemyCoin); //コインの追加処理
	void addAttributeAccumulation(const int& attribute, const int& attributeValue); //属性値の蓄積処理

	vector<int> status;
	vector<int> possessionItem;
	vector<int> possessionAccessory;
	vector<int> possessionJewel;
	vector<int> possessionMineral;

	Player(Input& input, MapDraw& draw_);
	~Player();

	void update(); //更新処理
};

//----------------------------------------------------------------------------------//
