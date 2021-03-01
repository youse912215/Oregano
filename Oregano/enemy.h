#pragma once
#include "player.h"
#include "dataSource.h"
#include <vector>

using namespace std;

class Enemy {
private:
	Player& player; //プレイヤークラスから
	DataSource source;

	Vec2 pos; //全体マップの座標
	Vec2 center; //全体マップの中心座標
	Vec2 distance; //プレイヤーとの距離
	Vec2 distanceSquared; //距離の2乗
	Vec2 distanceNormalized; //正規化した距離
	Vec2 moveSpeed; //移動速度

	Vec2 screenPos; //画面上の座標
	Vec2 screenCenter; //画面上の中心座標
	Vec2 relativeDistance; //プレイヤーとの相対距離

	int attackPower;

	void draw(); //描画処理

	void getMoveSpeed(); //移動速度取得
	void move(); //移動処理
	void dead(); //死亡処理

	void relativeDistanceUpdate(); //プレイヤーとの相対距離の更新

	void hitKnife(); //ナイフヒット時の処理
	void hitSlash(); //刃ヒット時の処理

	void collision(); //プレイヤーとの衝突判定

	void initPosition(); //初期位置の取得

	//出現位置を取得
	double getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2);

	bool onScreenX(); //画面上のx座標にいる条件
	bool onScreenY(); //画面上のy座標にいる条件

	vector<int> coin;
	
	int attribute;
	vector<int> attributeValue;
	void getAttribute();

public:
	bool activity;
	bool alive;

	Enemy(Player& player);
	~Enemy();

	void update(); //更新処理
};
