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
	Input& input; //入力クラス
	MapDraw& draw_; //マップ描画クラス
	DataSource& source; //データソースクラス

	Vec2d pos; //プレイヤー座標

	vector<int> cooldown; //アクションのクールダウン
	vector<bool> cooldownFlag; //クールダウンのフラグ

	bool damageFlag; //ダメージフラグ

	void draw(); //描画処理

	void actionCommand(); //アクションコマンドの処理

	void knifeUpdate(); //ナイフ更新処理
	void slashUpdate(); //刃更新処理
	void shieldUpdate(); //シールド更新処理
	void stateUpdate(); //状態更新処理

public:
	Vec2d center; //プレイヤーの中心座標
	Vec2d knifeCenter; //ナイフの中心座標
	Vec2d slashCenter; //刃の中心座標

	vector<bool> actionFlag; //アクションフラグ

	Player(Input& input, MapDraw& draw_, DataSource& source);
	~Player();

	int addDamage(const int& act); //敵へのダメージ
	int currentMapPos(const int& pos); //現在のマップを返す

	void lostPlayerCoin(const int& attackPower); //コインの損失処理
	void addPlayerCoin(const int& attribute, const int& enemyCoin); //コインの追加処理
	void addAttributeAccumulation(const int& attribute, const int& attributeValue); //属性値の蓄積処理
	void update(); //更新処理
};
