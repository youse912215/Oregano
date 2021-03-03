#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"
#include <vector>

using namespace std;

//プレイヤー
class Player {
private:
	Input& input; //入力クラスから
	DataSource source; //データソースクラスから

	Vec2d pos; //プレイヤー座標


	vector<int> cooldown; //アクションのクールダウン
	vector<bool> cooldownFlag; //クールダウンのフラグ

	void draw(); //描画処理

	void actionCommand(); //アクションコマンドの処理


	void knifeUpdate(); //ナイフ更新処理
	void slashUpdate(); //刃更新処理
	void shieldUpdate(); //シールド更新処理

	void coinUpdate();
	vector<int> coin;

	vector<int> attributeAccumulation; //属性耐久値

	int battleStyle; //戦闘スタイル（0:花萌葱, 1:深支子, 2:燕子花, 3:中紅花）
	void changeBattleStyle(const int& dir); //戦闘スタイルを切り替える
	void battleStyleUpdate();

	vector<bool> stateAbnormal; //状態異常（0:猛毒、1:痙攣、2:混乱、3:出血）


public:
	Vec2d center; //プレイヤーの中心座標
	Vec2d knifeCenter; //ナイフの中心座標
	Vec2d slashCenter; //刃の中心座標

	bool knife;
	bool slash;
	bool shield;

	void lostPlayerCoin(const int& attackPower); //コインの損失処理
	void addPlayerCoin(const int& attribute, const int& enemyCoin); //コインの追加処理

	void addAttributeAccumulation(const int& attribute, const int& attributeValue);

	vector<int> status;
	vector<int> possessionItem;
	vector<int> possessionAccessory;
	vector<int> possessionJewel;
	vector<int> possessionMineral;

	Player(Input& input);
	~Player();

	void update(); //更新処理
};

//----------------------------------------------------------------------------------//
