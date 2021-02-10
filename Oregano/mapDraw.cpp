#include "mapDraw.h"
#include "coordinate_confirmation.h"
#include "mapInformation.h"
#include "DxLib.h"

int MapDraw::mapX = INITIAL_X; //x方向
int MapDraw::mapY = INITIAL_Y; //y方向

MapDraw::MapDraw(int graph) : graph(graph),

                              information{FLOOR, HOUSE, SHALLOW, TIDE, WATER, STONE, WOODS},

                              currentCorner{
	                              ((mapX - 32) / BLOCK_SIZE) % 25, ((mapX + 31) / BLOCK_SIZE) % 25,
	                              ((mapY - 48) / BLOCK_SIZE) % 25, ((mapY + 15) / BLOCK_SIZE) % 25,
	                              ((mapX - 16) / BLOCK_SIZE) % 25, ((mapY - 32) / BLOCK_SIZE) % 25,
	                              ((mapX + 16) / BLOCK_SIZE) % 25, (mapY / BLOCK_SIZE) % 25,
                              },

                              boundaryCriteria{
	                              currentCorner[LEFT] == AREA_MAX && currentCorner[RIGHT] == AREA_MIN
	                              && currentMap.x == currentBoundaryMap.x,
	                              currentCorner[LEFT] == AREA_MAX && currentCorner[RIGHT] == AREA_MIN
	                              && currentMap.x != currentBoundaryMap.x,
	                              currentCorner[UP] == AREA_MAX && currentCorner[DOWN] == AREA_MIN
	                              && currentMap.y == currentBoundaryMap.y,
	                              currentCorner[UP] == AREA_MAX && currentCorner[DOWN] == AREA_MIN
	                              && currentMap.y != currentBoundaryMap.y
                              },

                              mapTopLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapTopCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapTopRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapLeftCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapRightCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)),

                              collisionFlag(12) {
	/* 行列番号 */
	matrix.x = 0;
	matrix.y = 0;
	/* 画面上の座標 */
	screen.x = INITIAL_X - mapX;
	screen.y = INITIAL_Y - mapY;
	/* 1マップあたりの配列サイズ */
	mapAspectSize.x = mapBase.at(0).size();
	mapAspectSize.y = mapBase.size();
	/* 現在のマップ座標 */
	currentMap.x = mapX / (BLOCK_SIZE * mapAspectSize.x);
	currentMap.y = mapY / (BLOCK_SIZE * mapAspectSize.y);
	/* 現在のマップの境界座標 */
	currentBoundaryMap.x = (mapX + 31) / (BLOCK_SIZE * mapAspectSize.x);
	currentBoundaryMap.y = (mapY + 15) / (BLOCK_SIZE * mapAspectSize.y);
	/* マップの中央位置 */
	centerPos.x = currentMap.x - 8;
	centerPos.y = currentMap.y - 8;
	/* マップ間距離（800px） */
	mapBetweenDistance = BLOCK_SIZE * AREA_WIDTH;
	/* 1ブロック区画（マップ）内の座標 */
	blockArea.x = (mapX / BLOCK_SIZE) % AREA_WIDTH;
	blockArea.y = (mapY / BLOCK_SIZE) % AREA_HEIGHT;
}

MapDraw::~MapDraw() {
}

/// <summary>
/// 読み込んだマップに描画する
/// </summary>
/// <param name="mapInformation"></param>
/// <param name="dirX">x方向の中心からの距離</param>
/// <param name="dirY">y方向の中心からの距離</param>
/// <param name="map">マップの配列</param>
void MapDraw::current_map_drawing(const int& mapInformation, const int& dirX, const int& dirY,
                                  vector<vector<int>>& map) {

	mapName(&matrix.y, &matrix.x, mapInformation); //マップ情報から列と行を取り出す
	//マップの描画
	for (int y = 0; y < mapAspectSize.y; y++) {
		for (int x = 0; x < mapAspectSize.x; x++) {
			//mapInformationのチップをDestの位置に描画
			if (map[y][x] == mapInformation) {
				DrawRectGraph(
					x * BLOCK_SIZE + screen.x + mapBetweenDistance * dirX,
					y * BLOCK_SIZE + screen.y + mapBetweenDistance * dirY,
					matrix.y * BLOCK_SIZE, matrix.x * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE,
					graph, true, false);
			}
		}
	}
}

/// <summary>
/// マップ名情報による現在マップの描画
/// </summary>
void MapDraw::drawing_current_maps(vector<vector<int>>& map, const int& dirX, const int& dirY) {
	fileImport(currentMap.x + dirX, currentMap.y + dirY, map); //csvファイル読み込み
	/*マップチップ描画*/
	current_map_drawing(FLOOR, centerPos.x + dirX, centerPos.y + dirY, map);
	current_map_drawing(HOUSE, centerPos.x + dirX, centerPos.y + dirY, map);
	current_map_drawing(SHALLOW, centerPos.x + dirX, centerPos.y + dirY, map);
	current_map_drawing(WATER, centerPos.x + dirX, centerPos.y + dirY, map);
	current_map_drawing(WOODS, centerPos.x + dirX, centerPos.y + dirY, map);
}

/// <summary>
/// 更新処理
/// </summary>
void MapDraw::update() {

	/* 9か所のマップを描画 */
	drawing_current_maps(mapCentral, Central, Central); //中央マップ（常に表示）

	//y方向のマップ描画判定
	if (blockArea.y <= TOP_BOUNDARY)
		drawing_current_maps(mapTopCentral, Central, Top); //上マップ
	else if (blockArea.y >= BOTTOM_BOUNDARY)
		drawing_current_maps(mapBottomCentral, Central, Bottom); //下マップ

	//x方向のマップ描画判定
	if (blockArea.x <= LEFT_BOUNDARY)
		drawing_current_maps(mapLeftCentral, Left, Central); //左マップ
	else if (blockArea.x >= RIGHT_BOUNDARY)
		drawing_current_maps(mapRightCentral, Right, Central); //右マップ

	//斜め方向のマップ描画判定
	if (blockArea.x <= LEFT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		drawing_current_maps(mapTopLeft, Left, Top); //左上マップ
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		drawing_current_maps(mapTopRight, Right, Top); //右上マップ
	else if (blockArea.x <= LEFT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		drawing_current_maps(mapBottomLeft, Left, Bottom); //左下マップ
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		drawing_current_maps(mapBottomRight, Right, Bottom); //右下マップ

	/* 12ヵ所で衝突判定を行う */
	collisionDetection(LEFT, UP, LEFT_UP); //左上
	collisionDetection(RIGHT, UP, RIGHT_UP); //右上
	collisionDetection(LEFT, DOWN, LEFT_DOWN); //左下
	collisionDetection(RIGHT, DOWN, RIGHT_DOWN); //右下

	collisionDetection(LEFT, CENTER_Y1, CENTER_LEFT1); //中央左1
	collisionDetection(RIGHT, CENTER_Y1, CENTER_RIGHT1); //中央右1
	collisionDetection(CENTER_X1, UP, CENTER_UP1); //中央上1
	collisionDetection(CENTER_X1, DOWN, CENTER_DOWN1); //中央下1

	collisionDetection(LEFT, CENTER_Y2, CENTER_LEFT2); //中央左2
	collisionDetection(RIGHT, CENTER_Y2, CENTER_RIGHT2); //中央右2
	collisionDetection(CENTER_X2, UP, CENTER_UP2); //中央上2
	collisionDetection(CENTER_X2, DOWN, CENTER_DOWN2); //中央下2

	DrawFormatString(150, 0, GetColor(255, 255, 255), "LU:%d, RU:%d",
	                 mapCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(300, 0, GetColor(255, 255, 255), "LD:%d, RD:%d",
	                 mapCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);
	DrawFormatString(450, 0, GetColor(255, 255, 255), "CL:%d, CR:%d, CU:%d, CD:%d",
	                 mapCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]],
	                 mapCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]], false);
	DrawFormatString(150, 15, GetColor(255, 255, 255), "L:%d, R:%d",
	                 currentCorner[LEFT], currentCorner[RIGHT], false);
	DrawFormatString(300, 15, GetColor(255, 255, 255), "U:%d, D:%d",
	                 currentCorner[UP], currentCorner[DOWN], false);
	DrawFormatString(450, 15, GetColor(255, 255, 255), "CX:%d, CY:%d",
	                 currentCorner[CENTER_X1], currentCorner[CENTER_Y1], false);
	DrawFormatString(150, 30, GetColor(255, 255, 255),
	                 "(cy:%d, cx:%d)", currentCorner[CENTER_Y1], currentCorner[CENTER_X1], false);

	DrawFormatString(0, 15, GetColor(255, 255, 255), "(iniY:%d, iniX:%d)", centerPos.y, centerPos.x, false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d, %d", currentMap.y, currentMap.x, false);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "cby%d, cbx%d",
	                 currentBoundaryMap.y, currentBoundaryMap.x, false);
}

//--- 4方向（上下左右）の衝突判定の結果を返す ---//
bool MapDraw::leftCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_LEFT1])
		|| (collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_LEFT2]));
}

bool MapDraw::rightCollisionFlag() {
	return ((collisionFlag[RIGHT_UP] && collisionFlag[CENTER_RIGHT1])
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_RIGHT2]));
}

bool MapDraw::upCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_UP1])
		|| (collisionFlag[RIGHT_UP] && collisionFlag[CENTER_UP2]));
}

bool MapDraw::downCollisionFlag() {
	return ((collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_DOWN1])
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_DOWN2]));
}

//----------------------------------------//

/// <summary>
/// 指定した位置の衝突判定を得る
/// </summary>
/// <param name="x">x軸の方向</param>
/// <param name="y">y軸の方向</param>
/// <param name="direction">判定方向</param>
void MapDraw::collisionDetection(const int& x, const int& y, const int& direction) {

	/*マップ境界線付近のとき、上下左右のマップで座標を得る*/
	if (x == LEFT) {
		//左方向
		if (boundaryCriteria[x])
			collisionFlag[direction] = (mapLeftCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
		else
			collisionFlag[direction] = (mapCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
	}

	if (x == RIGHT) {
		//右方向
		if (boundaryCriteria[x])
			collisionFlag[direction] = (mapRightCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
		else
			collisionFlag[direction] = (mapCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
	}

	if (y == UP) {
		//上方向
		if (boundaryCriteria[y])
			collisionFlag[direction] = (mapTopCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
		else
			collisionFlag[direction] = (mapCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
	}

	if (y == DOWN) {
		//下方向
		if (boundaryCriteria[y])
			collisionFlag[direction] = (mapBottomCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
		else
			collisionFlag[direction] = (mapCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
	}
}
