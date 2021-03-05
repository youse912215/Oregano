#pragma once
#include "player.h"
#include "dataSource.h"
#include "effectBlood.h"
#include <vector>

using namespace std;

class Enemy {
private:
	Vec2d pos; //全体マップの座標
	Vec2d center; //全体マップの中心座標
	Vec2d screenCenter; //画面上の中心座標

	Vec2d relativeDistance; //プレイヤーとの相対距離


	void draw(DataSource& source); //描画処理

	void dead(); //死亡処理

	void relativeDistanceUpdate(Player& player); //プレイヤーとの相対距離の更新

	void hitKnife(Player& player); //ナイフヒット時の処理
	void hitSlash(); //刃ヒット時の処理

	void collision(Player& player); //プレイヤーとの衝突判定

	void initPosition(Player& player); //初期位置の取得

	//出現位置を取得
	double getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2);

	void countDeadTime(); //死亡時間をカウント

	int life; //ライフ
	vector<int> initLife; //初期ライフ
	vector<int> possessionCoin; //所持コイン
	vector<int> attackPower; //攻撃力
	int level; //レベル

	vector<int> damageInterval; //ダメージ間隔
	vector<bool> damageFlag; //ダメージフラグ
	void takeDamage(const int& act); //ダメージを受ける
	void damageProcess(Player& player, const int& act); //ダメージ処理
	void noLife(Player& player); //0ライフ処理

	vector<int> attributeValue;
	void setStatus(); //ステータスを設定

	Vec2d lissajousSpeed; //移動速度
	const double lissajousMaxTime; //リサージュを制御する時間
	const double lissajousX; //リサージュ横幅
	const double lissajousY; //リサージュの縦幅
	const double controlSpeed; //制御速度
	double lissajousTime; //リサージュ用の時間
	int lissajousRandom; //リサージュ用のランダム変数
	void countTime(); //リサージュ用のカウント処理
	void lissajous(); //リサージュ曲線を描く

	int pattern; //出現パターン

public:
	Vec2d screenPos; //画面上の座標

	int deadTime; //死亡時間（復活までの時間）
	int attribute; //属性
	bool activity; //活動状態
	bool deadFlag; //死亡フラグ
	vector<bool> intervalFlag; //間隔フラグ

	Enemy();
	~Enemy();

	void update(Player& player, DataSource& source); //更新処理
	void initialize(Player& player);
};
