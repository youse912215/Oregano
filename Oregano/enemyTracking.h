#pragma once
#include "player.h"
#include "vec2.h"

class EnemyTracking {
private:
	Vec2d distance; //プレイヤーとの距離
	Vec2d distanceSquared; //距離の2乗
	Vec2d distanceNormalized; //正規化した距離
	Vec2d moveSpeed; //移動速度

	const int magnification; //倍率
	const int onLineDistance; //直線上の距離

	bool onScreenX(Vec2d& screenPos); //画面上のx座標にいる条件
	bool onScreenY(Vec2d& screenPos); //画面上のy座標にいる条件

	int moveOnLineX(Player& player, Vec2d& screenPos); //直線上の移動(x方向)
	int moveOnLineY(Player& player, Vec2d& screenPos); //直線上の移動(y方向)

	void getMoveSpeed(Player& player, Vec2d& pos); //移動速度取得
	void move(Player& player, Vec2d& pos, Vec2d& screenPos); //移動処理

public:
	EnemyTracking();

	void update(Player& player, Vec2d& pos, Vec2d& screenPos); //更新処理
};
