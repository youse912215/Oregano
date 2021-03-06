#include "mapCollision.h"
#include "playerState.h"
#include "constant.h"
#include "mapDraw.h"
#include <algorithm>

MapCollision::MapCollision(MapDraw& map) :
	map(map), collisionFlag(12), boundaryCriteria(9), needCoin{70, 55, 40, 25}, index(0) {
}

MapCollision::~MapCollision() {
}

/// <summary>
/// 初期化
/// </summary>
void MapCollision::initialize() {
	boundaryCriteria = {
			//左条件
			map.currentCorner[LEFT] == AREA_MAX
			&& map.currentCorner[RIGHT] == AREA_MIN
			&& map.currentMap.x >= map.currentBoundaryMap1.x
			&& map.currentMap.x == map.currentBoundaryMap2.x,

			//右条件
			map.currentCorner[LEFT] == AREA_MAX
			&& map.currentCorner[RIGHT] == AREA_MIN
			&& map.currentMap.x == map.currentBoundaryMap1.x
			&& map.currentMap.x <= map.currentBoundaryMap2.x,

			//上条件
			map.currentCorner[UP] == AREA_MAX
			&& map.currentCorner[DOWN] == AREA_MIN
			&& map.currentMap.y >= map.currentBoundaryMap1.y
			&& map.currentMap.y ==
			map.currentBoundaryMap2.y,

			//下条件
			map.currentCorner[UP] == AREA_MAX
			&& map.currentCorner[DOWN] == AREA_MIN
			&& map.currentMap.y == map.currentBoundaryMap1.y
			&& map.currentMap.y <= map.currentBoundaryMap2.y,

			//中央横1条件
			map.currentCorner[CENTER_X1] == AREA_MAX
			&& map.currentCorner[CENTER_X2] == AREA_MIN
			&& map.currentMap.x >= map.currentBoundaryMap1.x
			&& map.currentMap.x == map.currentBoundaryMap2.x,

			//中央横2条件
			map.currentCorner[CENTER_X1] == AREA_MAX
			&& map.currentCorner[CENTER_X2] == AREA_MIN
			&& map.currentMap.x == map.currentBoundaryMap1.x
			&& map.currentMap.x <= map.currentBoundaryMap2.x,

			//中央縦1条件
			map.currentCorner[CENTER_Y1] == AREA_MAX
			&& map.currentCorner[CENTER_Y2] == AREA_MIN
			&& map.currentMap.y >= map.currentBoundaryMap1.y
			&& map.currentMap.y == map.currentBoundaryMap2.y,

			//中央縦2条件
			map.currentCorner[CENTER_Y1] == AREA_MAX
			&& map.currentCorner[CENTER_Y2] == AREA_MIN
			&& map.currentMap.y == map.currentBoundaryMap1.y
			&& map.currentMap.y <= map.currentBoundaryMap2.y,

			//境界線交差時の条件
			map.currentCorner[LEFT] == AREA_MAX && map.currentCorner[RIGHT] == AREA_MIN
			&& map.currentCorner[UP] == AREA_MAX && map.currentCorner[DOWN] == AREA_MIN
			&& map.currentMap.x == map.currentBoundaryMap1.x
			&& map.currentMap.y > map.currentBoundaryMap1.y
			&& map.currentMap.x < map.currentBoundaryMap2.x
			&& map.currentMap.y == map.currentBoundaryMap2.y
		};
}

/// <summary>
/// 更新処理
/// </summary>
void MapCollision::update() {

	initialize(); //初期化

	/* 12ヵ所で衝突判定を行う */
	collisionDetectionLeftUp(); //左上
	collisionDetectionLeftDown(); //右上
	collisionDetectionRightUp(); //左下
	collisionDetectionRightDown(); //右下

	collisionDetectionCenterLeft1(); //中央左1
	collisionDetectionCenterLeft2(); //中央左2
	collisionDetectionCenterRight1(); //中央右1
	collisionDetectionCenterRight2(); //中央右2

	collisionDetectionCenterUp1(); //中央上1
	collisionDetectionCenterUp2(); //中央上2
	collisionDetectionCenterDown1(); //中央下1
	collisionDetectionCenterDown2(); //中央下2
}

//--- 各衝突判定部分における衝突フラグ ---//
//現在位置におけるcollisionDetection関数がtrueかfalseかを更新する

/// <summary>
/// 左上の衝突判定
/// </summary>
void MapCollision::collisionDetectionLeftUp() {
	//マップの境界線が交差点付近のとき
	if (boundaryCriteria[CROSS])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_TOP_LEFT, LEFT, UP)) ? true : false;
		//マップの境界線が左のとき
	else if (boundaryCriteria[LEFT])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, UP)) ? true : false;
		//マップの境界線が上のとき
	else if (boundaryCriteria[UP])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_TOP_CENTRAL, LEFT, UP)) ? true : false;
		//それ以外
	else
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_CENTRAL, LEFT, UP)) ? true : false;
}

/// <summary>
/// 右上の衝突判定
/// </summary>
void MapCollision::collisionDetectionRightUp() {
	//マップの境界線が交差点付近のときまたは、上のとき
	if (boundaryCriteria[CROSS] || boundaryCriteria[UP])
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_TOP_CENTRAL, RIGHT, UP)) ? true : false;
		//マップの境界線が右のとき
	else if (boundaryCriteria[RIGHT])
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, UP)) ? true : false;
		//それ以外
	else
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_CENTRAL, RIGHT, UP)) ? true : false;
}

/// <summary>
/// 左下の衝突判定
/// </summary>
void MapCollision::collisionDetectionLeftDown() {
	//マップの境界線が交差点付近のときまたは、左のとき
	if (boundaryCriteria[LEFT] || boundaryCriteria[CROSS])
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, DOWN)) ? true : false;
		//マップの境界線が下のとき
	else if (boundaryCriteria[DOWN])
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_BOTTOM_CENTRAL, LEFT, DOWN)) ? true : false;
		//それ以外
	else
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_CENTRAL, LEFT, DOWN)) ? true : false;
}

/// <summary>
/// 右下の衝突判定
/// </summary>
void MapCollision::collisionDetectionRightDown() {
	//マップの境界線が右のとき
	if (boundaryCriteria[RIGHT])
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, DOWN)) ? true : false;
		//マップの境界線が下のとき
	else if (boundaryCriteria[DOWN])
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_BOTTOM_CENTRAL, RIGHT, DOWN)) ? true : false;
		//それ以外
	else
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_CENTRAL, RIGHT, DOWN)) ? true : false;
}

/// <summary>
/// 左中央1の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterLeft1() {
	//マップの境界線が中央上のとき
	if (boundaryCriteria[CENTER_Y1])
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_TOP_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
		//マップの境界線が左のとき
	else if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
		//それ以外
	else
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
}

/// <summary>
/// 左中央2の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterLeft2() {
	//マップの境界線が左のとき
	if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT2] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, CENTER_Y2)) ? true : false;
		//それ以外
	else
		collisionFlag[CENTER_LEFT2] = (collisionDetection(MAP_CENTRAL, LEFT, CENTER_Y2)) ? true : false;
}

/// <summary>
/// 右中央1の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterRight1() {
	//マップの境界線が中央上のとき
	if (boundaryCriteria[CENTER_Y1])
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_TOP_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
		//マップの境界線が右のとき
	else if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
		//それ以外
	else
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
}

/// <summary>
/// 右中央2の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterRight2() {
	//マップの境界線が右のとき
	if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT2] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, CENTER_Y2)) ? true : false;
		//それ以外
	else
		collisionFlag[CENTER_RIGHT2] = (collisionDetection(MAP_CENTRAL, RIGHT, CENTER_Y2)) ? true : false;
}

/// <summary>
/// 上中央1の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterUp1() {
	//マップの境界線が中央左のとき
	if (boundaryCriteria[CENTER_X1])
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_LEFT_CENTRAL, CENTER_X1, UP)) ? true : false;
		//マップの境界線が上のとき
	else if (boundaryCriteria[UP])
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_TOP_CENTRAL, CENTER_X1, UP)) ? true : false;
		//それ以外
	else
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_CENTRAL, CENTER_X1, UP)) ? true : false;
}

/// <summary>
/// 上中央2の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterUp2() {
	//マップの境界線が中央右のとき
	if (boundaryCriteria[CENTER_X2])
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_RIGHT_CENTRAL, CENTER_X2, UP)) ? true : false;
		//マップの境界線が上のとき
	else if (boundaryCriteria[UP])
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_TOP_CENTRAL, CENTER_X2, UP)) ? true : false;
		//それ以外
	else
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_CENTRAL, CENTER_X2, UP)) ? true : false;
}

/// <summary>
/// 下中央1の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterDown1() {
	//マップの境界線が中央左のとき
	if (boundaryCriteria[CENTER_X1])
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_LEFT_CENTRAL, CENTER_X1, DOWN)) ? true : false;
		//マップの境界線が下のとき
	else if (boundaryCriteria[DOWN])
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_BOTTOM_CENTRAL, CENTER_X1, DOWN)) ? true : false;
		//それ以外
	else
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_CENTRAL, CENTER_X1, DOWN)) ? true : false;
}

/// <summary>
/// 下中央2の衝突判定
/// </summary>
void MapCollision::collisionDetectionCenterDown2() {
	//マップの境界線が中央右のとき
	if (boundaryCriteria[CENTER_X2])
		collisionFlag[CENTER_DOWN2] = (collisionDetection(MAP_RIGHT_CENTRAL, CENTER_X2, DOWN)) ? true : false;
		//マップの境界線が下のとき
	else if (boundaryCriteria[DOWN])
		collisionFlag[CENTER_DOWN2] = (collisionDetection(MAP_BOTTOM_CENTRAL, CENTER_X2, DOWN)) ? true : false;
		//それ以外
	else
		collisionFlag[CENTER_DOWN2] = (collisionDetection(MAP_CENTRAL, CENTER_X2, DOWN)) ? true : false;
}

//----------------------------------------//

/// <summary>
/// 判定を行うマップとそのマップの座標の組み合わせで衝突判定をとる
/// 結果をbool値で返す
/// </summary>
/// <param name="dirXY">判定を行うマップ名</param>
/// <param name="dirX">判定対象のx座標</param>
/// <param name="dirY">判定対象のy座標</param>
bool MapCollision::collisionDetection(const int& dirXY, const int& dirX, const int& dirY) {

	/* 判定箇所がWALL(壁)と重なっているならtrueを返す */
	switch (dirXY) {
	case MAP_TOP_LEFT: //左上マップ
		return map.mapTopLeft[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_TOP_CENTRAL: //中央上マップ
		return map.mapTopCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_TOP_RIGHT: //右上マップ
		return map.mapTopRight[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_LEFT_CENTRAL: //左中央マップ
		return map.mapLeftCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_CENTRAL: //中央マップ
		return map.mapCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_RIGHT_CENTRAL: //右中央マップ
		return map.mapRightCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_BOTTOM_LEFT: //左下マップ
		return map.mapBottomLeft[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_BOTTOM_CENTRAL: //中央下マップ
		return map.mapBottomCentral[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	case MAP_BOTTOM_RIGHT: //右下マップ
		return map.mapBottomRight[map.currentCorner[dirY]][map.currentCorner[dirX]] >= collisionRange();
	default:
		return false; //それ以外はfalseを返す
	}
}

/// <summary>
/// 衝突範囲を返す
/// </summary>
/// <returns></returns>
int MapCollision::collisionRange() {
	vector<int>::iterator itr; //イテレータ宣言

	//いずれかのコインがj枚以上であれば、その枚数に対応する床の通過を許可
	for (auto j : needCoin) {
		for (unsigned int i = 0; i != PlayerState::coin.size(); ++i) {

			itr = find(needCoin.begin(), needCoin.end(), j); //必要コインがj枚であるか探索する

			//コインiがj毎未満のとき
			if (PlayerState::coin[i] < j) continue; //条件以外なら、処理をスキップする

			index = distance(needCoin.begin(), itr); //イテレータのインデックスを取得
			return WALL - index; //必要のコインの枚数に対応する床を返す
		}
	}
	//それ以外
	return FLOOR_GREEN; //花萌葱床
}

//左上（3点）方向の衝突判定
bool MapCollision::leftUpCollisionFlag() {
	//左上、中央上1（左上と中央上の間）、中央左1（左上と中央左の間）
	return collisionFlag[LEFT_UP] && collisionFlag[CENTER_UP1] && collisionFlag[CENTER_LEFT1];
}

//右上（3点）方向の衝突判定
bool MapCollision::rightUpCollisionFlag() {
	//右上、中央上2（右上と中央上の間）、中央右1（右上と中央右の間）
	return collisionFlag[RIGHT_UP] && collisionFlag[CENTER_UP2] && collisionFlag[CENTER_RIGHT1];
}

//左下（3点）方向の衝突判定
bool MapCollision::leftDownCollisionFlag() {
	//左下、中央下1（左下と中央下の間）、中央左2（左下と中央左の間）
	return collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_DOWN1] && collisionFlag[CENTER_LEFT2];
}

//右下（3点）方向の衝突判定
bool MapCollision::rightDownCollisionFlag() {
	//右下、中央下2（右下と中央下の間）、中央右2（右下と中央右の間）
	return collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_DOWN2] && collisionFlag[CENTER_RIGHT2];
}

//--- 4方向（上下左右）の衝突判定の結果を返す ---//
//左方向
bool MapCollision::leftCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_LEFT1]) //左上と中央左1
		|| (collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_LEFT2]) //左下と中央左2
		|| (collisionFlag[CENTER_LEFT1] && collisionFlag[CENTER_LEFT2]) //中央左1と中央左2
		|| leftUpCollisionFlag() //左上3点
		|| leftDownCollisionFlag()); //左下3点
}

//右方向
bool MapCollision::rightCollisionFlag() {
	return ((collisionFlag[RIGHT_UP] && collisionFlag[CENTER_RIGHT1]) //右上と中央右1
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_RIGHT2]) //右下と中央右2
		|| (collisionFlag[CENTER_RIGHT1] && collisionFlag[CENTER_RIGHT2]) //中央右1と中央右2
		|| rightUpCollisionFlag() //右上3点
		|| rightDownCollisionFlag()); //右下3点
}

//上方向
bool MapCollision::upCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_UP1]) //左上と中央上1
		|| (collisionFlag[RIGHT_UP] && collisionFlag[CENTER_UP2]) //右上と中央上2
		|| (collisionFlag[CENTER_UP1] && collisionFlag[CENTER_UP2]) //中央上1と中央上2
		|| leftUpCollisionFlag() //左上3点
		|| rightUpCollisionFlag()); //右上3点
}

//下方向
bool MapCollision::downCollisionFlag() {
	return ((collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_DOWN1]) //左下と中央下1
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_DOWN2]) //右下と中央下2
		|| (collisionFlag[CENTER_DOWN1] && collisionFlag[CENTER_DOWN2]) //中央下1と中央下2
		|| leftDownCollisionFlag() //左下3点
		|| rightDownCollisionFlag()); //右下3点
}

//----------------------------------------//
