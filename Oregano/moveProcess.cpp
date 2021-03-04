#include "moveProcess.h"

bool MoveProcess::mapCondition(MapDraw& draw, const int& mapInfo) {
	return draw.mapCentral[draw.blockArea.y][draw.blockArea.x] == mapInfo;
}

/// <summary>
/// 現在のマップの情報によって、移動距離を返す
/// </summary>
/// <param name="draw">マップ描画クラス</param>
/// <param name="mapInfo">マップ情報</param>
int MoveProcess::movingDistance(MapDraw& draw) {
	//浅瀬のとき
	if (mapCondition(draw, SHALLOW))
		return MOVING_DISTANCE / 2; //移動距離を1/2
	//水沼のとき
	if (mapCondition(draw, SWAMP))
		return MOVING_DISTANCE / 4; //移動距離を1/4
	//それ以外
	return MOVING_DISTANCE; //通常の移動距離
}

/// <summary>
/// 左移動
/// </summary>
void MoveProcess::left(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapX -= movingDistance(draw);
	if (collision.leftCollisionFlag()) MapDraw::mapX += movingDistance(draw);
}

/// <summary>
/// 右移動
/// </summary>
void MoveProcess::right(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapX += movingDistance(draw);
	if (collision.rightCollisionFlag()) MapDraw::mapX -= movingDistance(draw);
}

/// <summary>
/// 上移動
/// </summary>
void MoveProcess::up(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapY -= movingDistance(draw);
	if (collision.upCollisionFlag()) MapDraw::mapY += movingDistance(draw);
}

/// <summary>
/// 下移動
/// </summary>
void MoveProcess::down(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapY += movingDistance(draw);
	if (collision.downCollisionFlag()) MapDraw::mapY -= movingDistance(draw);
}
