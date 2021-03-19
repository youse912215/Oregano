#pragma once
#include "mapDraw.h"
#include <vector>

using namespace std;

class MapCollision {
private:
	MapDraw& map; //マップ描画クラスから

	vector<bool> collisionFlag; //衝突フラグ
	vector<bool> boundaryCriteria; //各方向の境界条件

	const int needCoin; //（特定の床通過に）必要なコイン

	int collisionRange(); //衝突範囲を返す

	//判定を行うマップとそのマップの座標の組み合わせで衝突判定をとる
	bool collisionDetection(const int& dirXY, const int& dirX, const int& dirY);

	/* 角部分の4方向の衝突フラグ */
	bool leftUpCollisionFlag(); //左上
	bool rightUpCollisionFlag(); //右上
	bool leftDownCollisionFlag(); //左下
	bool rightDownCollisionFlag(); //右下

	/* 各部分ごとの衝突判定 */
	void collisionDetectionLeftUp(); //左上
	void collisionDetectionRightUp(); //右上
	void collisionDetectionLeftDown(); //左下
	void collisionDetectionRightDown(); //右下
	void collisionDetectionCenterLeft1(); //左中央1（左上と中央左の間）
	void collisionDetectionCenterLeft2(); //左中央2（左下と中央左の間）
	void collisionDetectionCenterRight1(); //右中央1（右上と中央右の間）
	void collisionDetectionCenterRight2(); //右中央2（右下と中央右の間）
	void collisionDetectionCenterUp1(); //中央上1（左上と中央上の間）
	void collisionDetectionCenterUp2(); //中央上2（右上と中央上の間）
	void collisionDetectionCenterDown1(); //中央下1（左下と中央下の間）
	void collisionDetectionCenterDown2(); //中央下2（右下と中央下の間）

	void initialize(); //初期化

public:
	MapCollision(MapDraw& map);
	~MapCollision();

	void update(); //更新処理

	/* 上下左右4方向の衝突フラグ */
	bool leftCollisionFlag(); //左
	bool rightCollisionFlag(); //右
	bool upCollisionFlag(); //上
	bool downCollisionFlag(); //下
};
