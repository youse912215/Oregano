#pragma once
#include "mapDraw.h"
#include "mapCollision.h"

class MoveProcess {
private:
	bool collisionDirectionLeft(MapCollision& collision); //左の衝突判定
	bool collisionDirectionRight(MapCollision& collision); //右の衝突判定
	bool collisionDirectionUp(MapCollision& collision); //上の衝突判定
	bool collisionDirectionDown(MapCollision& collision); //下の衝突判定

	int movingDistance(MapDraw& draw); //移動距離
	int invert(); //方向を反転させる

public:
	bool mapCondition(MapDraw& draw, const int& mapInfo); //マップ条件

	int changeDirection(const int& dir); //方向の情報を切り替える

	void left(MapCollision& collision, MapDraw& draw); //左移動
	void right(MapCollision& collision, MapDraw& draw); //右移動
	void up(MapCollision& collision, MapDraw& draw); //上移動
	void down(MapCollision& collision, MapDraw& draw); //下移動
};
