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

	Vec2 pos; //プレイヤー座標
	Vec2 knifePos; //ナイフ座標
	Vec2 knifeAddPos; //ナイフの加算分の座標	
	Vec2 slashPos; //刃座標	
	Vec2 shieldPos; //シールド座標

	vector<int> cooldown; //アクションのクールダウン
	vector<bool> cooldownFlag; //クールダウンのフラグ

	void draw(); //描画処理

	void actionCommand(); //アクションコマンドの処理

	void knifeCooldown(); //ナイフのクールダウン処理
	void setKnifePosition(); //ナイフのポジジョンセット
	void resetKnifePosition(); //ナイフのポジジョンリセット
	void accelKnife(); //ナイフの加速
	void knifeUpdate(); //ナイフの更新処理
	bool deleteKnife(); //ナイフの削除条件

	void slashCooldown(); //刃のクールダウン処理

	int shieldValue; //シールド量
	void shieldCooldown(); //シールドのクールダウン処理
	void shieldUpdate(); //シールド更新処理


	void coinUpdate();
	int coin0;
	vector<int> coin;

	vector<int> attributeAccumulation; //属性耐久値

	int battleStyle; //戦闘スタイル（0:花萌葱, 1:深支子, 2:燕子花, 3:中紅花）
	void changeBattleStyle(const int& dir); //戦闘スタイルを切り替える
	void battleStyleUpdate();

public:
	Vec2 center; //プレイヤーの中心座標
	Vec2 knifeCenter; //ナイフの中心座標
	Vec2 slashCenter; //刃の中心座標

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
