#pragma once
#include "player.h"
#include "dataSource.h"
#include "effectParticle.h"
#include <vector>
#include "player.h"
#include "inputProcess.h"


using namespace std;

class Enemy {
private:
	//Player player(Input input); //プレイヤークラスから
	DataSource source;

	Vec2d pos; //全体マップの座標
	Vec2d center; //全体マップの中心座標
	Vec2d distance; //プレイヤーとの距離
	Vec2d distanceSquared; //距離の2乗
	Vec2d distanceNormalized; //正規化した距離
	Vec2d moveSpeed; //移動速度
	Vec2d screenCenter; //画面上の中心座標


	Vec2d relativeDistance; //プレイヤーとの相対距離

	int attackPower;

	void draw(); //描画処理

	void getMoveSpeed(Player& player); //移動速度取得
	void move(Player& player); //移動処理
	void dead(); //死亡処理

	void relativeDistanceUpdate(Player& player); //プレイヤーとの相対距離の更新

	void hitKnife(Player& player); //ナイフヒット時の処理
	void hitSlash(Player& player); //刃ヒット時の処理

	void collision(Player& player); //プレイヤーとの衝突判定

	void initPosition(); //初期位置の取得

	//出現位置を取得
	double getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2);

	bool onScreenX(); //画面上のx座標にいる条件
	bool onScreenY(); //画面上のy座標にいる条件

	vector<int> coin;


	vector<int> attributeValue;
	void getAttribute();

	void countDeadTime();

	void lissajous();
	Vec2d movePattern2;
	double lissajousTime;
	int lissajousRandom;

public:
	Vec2d screenPos; //画面上の座標

	int attribute;
	bool activity;
	bool deadFlag;
	int deadTime;


	Enemy();
	~Enemy();


	void update(Player& player); //更新処理
	void initProcess(Player& player);
};
