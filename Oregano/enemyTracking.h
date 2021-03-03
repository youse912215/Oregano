#pragma once
#include "player.h"
#include "vec2.h"

class EnemyTracking {
private:

public:
	Vec2d distance; //プレイヤーとの距離
	Vec2d distanceSquared; //距離の2乗
	Vec2d distanceNormalized; //正規化した距離
	Vec2d moveSpeed; //移動速度

	EnemyTracking();

	void getMoveSpeed(Player& player, Vec2d& pos); //移動速度取得
	void move(Player& player, Vec2d& pos, Vec2d& screenPos); //移動処理

	bool onScreenX(Vec2d& screenPos); //画面上のx座標にいる条件
	bool onScreenY(Vec2d& screenPos); //画面上のy座標にいる条件

	void update(Player& player, Vec2d& pos, Vec2d& screenPos); //更新処理
};
