#include "moveProcess.h"
#include "playerState.h"

PlayerState state_;


bool MoveProcess::mapCondition(MapDraw& draw, const int& mapInfo) {
	return draw.mapCentral[draw.blockArea.y][draw.blockArea.x] == mapInfo;
}

/// <summary>
/// 左衝突フラグ
/// </summary>
bool MoveProcess::collisionDirectionLeft(MapCollision& collision) {
	//混乱状態以外のとき
	if (!state_.condition[CONFUSION])
		return collision.leftCollisionFlag(); //そのまま返す
	return collision.rightCollisionFlag(); //反転して返す
}

/// <summary>
/// 右衝突フラグ
/// </summary>
bool MoveProcess::collisionDirectionRight(MapCollision& collision) {
	//混乱状態以外のとき
	if (!state_.condition[CONFUSION])
		return collision.rightCollisionFlag(); //そのまま返す
	return collision.leftCollisionFlag(); //反転して返す
}

/// <summary>
/// 上衝突フラグ
/// </summary>
bool MoveProcess::collisionDirectionUp(MapCollision& collision) {
	//混乱状態以外のとき
	if (!state_.condition[CONFUSION])
		return collision.upCollisionFlag(); //そのまま返す
	return collision.downCollisionFlag(); //反転して返す
}

/// <summary>
/// 下衝突フラグ
/// </summary>
bool MoveProcess::collisionDirectionDown(MapCollision& collision) {
	//混乱状態以外のとき
	if (!state_.condition[CONFUSION])
		return collision.downCollisionFlag(); //そのまま返す
	return collision.upCollisionFlag(); //反転して返す
}

/// <summary>
/// 現在のマップの情報によって、移動距離を返す
/// </summary>
/// <param name="draw">マップ描画クラス</param>
int MoveProcess::movingDistance(MapDraw& draw) {
	//戦闘スタイルが燕子花(対混乱)以外のとき
	if (PlayerState::battleStyle != CONFUSION) {
		//浅瀬のとき
		if (mapCondition(draw, SHALLOW))
			return MOVING_DISTANCE / 2; //移動距離を1/2
		//水沼のとき
		if (mapCondition(draw, SWAMP))
			return MOVING_DISTANCE / 4; //移動距離を1/4
		//氷のとき
		if (mapCondition(draw, ICE))
			return MOVING_DISTANCE * 2; //移動距離を2倍
	}
	//それ以外
	return MOVING_DISTANCE; //通常の移動距離
}

/// <summary>
/// 方向を反転
/// </summary>
int MoveProcess::invert() {
	//混乱状態以外のとき
	if (!PlayerState::condition[CONFUSION])
		return 1; //そのまま返す
	return -1; //反転して返す
}

/// <summary>
/// 方向の情報を切り替える
/// </summary>
/// <param name="dir">方向</param>
int MoveProcess::changeDirection(const int& dir) {
	if (!PlayerState::condition[CONFUSION]) return dir;
	if (dir == LEFT) return RIGHT; //左→右
	if (dir == RIGHT) return LEFT; //右→左
	if (dir == UP) return DOWN; //上→下
	if (dir == DOWN) return UP; //下→上
	return 0;
}

/// <summary>
/// 左移動
/// </summary>
void MoveProcess::left(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapX -= movingDistance(draw) * invert(); //通常時
	if (collisionDirectionLeft(collision))
		MapDraw::mapX += movingDistance(draw) * invert(); //衝突時
}

/// <summary>
/// 右移動
/// </summary>
void MoveProcess::right(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapX += movingDistance(draw) * invert(); //通常時
	if (collisionDirectionRight(collision))
		MapDraw::mapX -= movingDistance(draw) * invert(); //衝突時
}

/// <summary>
/// 上移動
/// </summary>
void MoveProcess::up(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapY -= movingDistance(draw) * invert(); //通常時
	if (collisionDirectionUp(collision))
		MapDraw::mapY += movingDistance(draw) * invert(); //衝突時
}

/// <summary>
/// 下移動
/// </summary>
void MoveProcess::down(MapCollision& collision, MapDraw& draw) {
	MapDraw::mapY += movingDistance(draw) * invert(); //通常時
	if (collisionDirectionDown(collision))
		MapDraw::mapY -= movingDistance(draw) * invert(); //衝突時
}
