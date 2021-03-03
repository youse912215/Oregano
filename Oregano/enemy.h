#pragma once
#include "player.h"
#include "dataSource.h"
#include "effectBlood.h"
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
	Vec2d screenCenter; //画面上の中心座標


	Vec2d relativeDistance; //プレイヤーとの相対距離

	void draw(); //描画処理

	void dead(); //死亡処理

	void relativeDistanceUpdate(Player& player); //プレイヤーとの相対距離の更新

	void hitKnife(Player& player); //ナイフヒット時の処理
	void hitSlash(Player& player); //刃ヒット時の処理

	void collision(Player& player); //プレイヤーとの衝突判定

	void initPosition(); //初期位置の取得

	//出現位置を取得
	double getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2);

	void countDeadTime(); //死亡時間をカウント

	vector<int> coin; //コイン
	vector<int> attackPower; //攻撃力
	int level; //レベル


	vector<int> attributeValue;
	void getAttribute(); //属性を棕櫚得
	void getLevel(); //レベルを取得


	void countTime(); //リサージュ用のカウント処理
	void lissajous(); //リサージュ曲線を描く
	Vec2d moveSpeed2; //移動速度
	double lissajousTime; //リサージュ用の時間
	int lissajousRandom; //リサージュ用のランダム変数

	int pattern;

public:
	Vec2d screenPos; //画面上の座標

	int attribute;
	bool activity;
	bool deadFlag;
	int deadTime;


	Enemy();
	~Enemy();


	void update(Player& player); //更新処理
	void initialize(Player& player);
};
