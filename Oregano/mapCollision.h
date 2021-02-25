#pragma once
#include "mapDraw.h"
#include <vector>

using namespace std;

class MapCollision {
private:
	MapDraw& map; //マップ描画クラスから

	/* 角部分の4方向の衝突フラグ */
	bool leftUpCollisionFlag();
	bool rightUpCollisionFlag();
	bool leftDownCollisionFlag();
	bool rightDownCollisionFlag();

	/* 各部分ごとの衝突判定 */
	void collisionDetectionLeftUp();
	void collisionDetectionRightUp();
	void collisionDetectionLeftDown();
	void collisionDetectionRightDown();
	void collisionDetectionCenterLeft1();
	void collisionDetectionCenterLeft2();
	void collisionDetectionCenterRight1();
	void collisionDetectionCenterRight2();
	void collisionDetectionCenterUp1();
	void collisionDetectionCenterUp2();
	void collisionDetectionCenterDown1();
	void collisionDetectionCenterDown2();

	//判定を行うマップとそのマップの座標の組み合わせで衝突判定をとる
	bool collisionDetection(const int& dirXY, const int& dirX, const int& dirY);

	int collisionRange(); //衝突範囲

	vector<bool> collisionFlag; //衝突フラグ
	vector<bool> boundaryCriteria; //各方向の境界条件

public:
	MapCollision(MapDraw& map);
	~MapCollision();

	void update(); //更新処理

	/* 上下左右4方向の衝突フラグ */
	bool leftCollisionFlag();
	bool rightCollisionFlag();
	bool upCollisionFlag();
	bool downCollisionFlag();
};
