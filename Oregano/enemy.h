#pragma once
#include "player.h"
#include "dataSource.h"
#include "effectBlood.h"
#include <vector>

using namespace std;

class Enemy {
private:
	/* 描画関係 */
	Vec2d pos; //全体マップの座標
	Vec2d center; //全体マップの中心座標
	Vec2d screenCenter; //画面上の中心座標
	Vec2d relativeDistance; //プレイヤーとの相対距離
	const int lifeHeight; //ライフ画像の縦幅

	/* 処理系 */
	void initPosition(Player& player); //初期位置の取得
	double getPopLocation(const int& mapDir, const int& coordinate1,
	                      const int& coordinate2); //出現位置を取得
	void relativeDistanceUpdate(Player& player); //プレイヤーとの相対距離の更新
	void collision(Player& player); //プレイヤーとの衝突判定

	void hitKnife(Player& player); //ナイフヒット時の処理
	void hitSlash(); //刃ヒット時の処理

	void dead(); //死亡処理
	void countDeadTime(); //死亡時間をカウント

	void draw(DataSource& source); //描画処理


	/* ステータス関係 */
	vector<int> initLife; //初期ライフ
	vector<int> possessionCoin; //所持コイン
	vector<int> attackPower; //攻撃力
	vector<int> attributeValue; //属性値

	int life; //ライフ
	int pattern; //出現パターン
	int level; //レベル
	const int maxLevel; //最大レベル

	void setStatus(Player& player); //ステータスを設定
	void getAttribute(Player& player); //属性値を取得

	/* ダメージ関係 */
	vector<int> damageInterval; //ダメージ間隔
	vector<bool> damageFlag; //ダメージフラグ

	const double knifeRange; //ナイフの範囲
	const int deadTimeMax; //最大死亡時間
	const int intervalMax; //最大間隔時間

	void takeDamage(const int& act); //ダメージを受ける
	void damageProcess(Player& player, const int& act, DataSource& source); //ダメージ処理
	void noLife(Player& player); //0ライフ処理


	/* リサージュ関係 */
	Vec2d lissajousSpeed; //移動速度
	const double lissajousMaxTime; //リサージュを制御する時間
	const double lissajousX; //リサージュ横幅
	const double lissajousY; //リサージュの縦幅
	const double controlSpeed; //制御速度
	double lissajousTime; //リサージュ用の時間
	int lissajousRandom; //リサージュ用のランダム変数
	void countTime(); //リサージュ用のカウント処理
	void lissajous(); //リサージュ曲線を描く

public:
	Vec2d screenPos; //画面上の座標

	int deadTime; //死亡時間（復活までの時間）
	int attribute; //属性
	bool activity; //活動状態
	bool deadFlag; //死亡フラグ
	vector<bool> intervalFlag; //間隔フラグ

	Enemy();
	~Enemy();

	void initialize(Player& player); //初期化
	void update(Player& player, DataSource& source); //更新処理
};
