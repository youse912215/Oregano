#include "mapDraw.h"
#include "coordinate_confirmation.h"
#include "mapInformation.h"
#include "DxLib.h"

int MapDraw::mapX = INITIAL_X; //x方向
int MapDraw::mapY = INITIAL_Y; //y方向

MapDraw::MapDraw(int graph) : graph(graph),

                              information{
	                              FLOOR, BEACH, FLOWER, MUSHROOM, HOUSE, SHALLOW, TIDE, WATER, CRYSTAL, STONE,
	                              MINERAL, WOODS, BRIDGE_WIDTH, BRIDGE_HEIGHT, TREASURE_BOX
                              },

                              currentCorner{
	                              ((mapX - 32) / BLOCK_SIZE) % 25, ((mapX + 31) / BLOCK_SIZE) % 25,
	                              ((mapY - 48) / BLOCK_SIZE) % 25, ((mapY + 15) / BLOCK_SIZE) % 25,
	                              ((mapX - 16) / BLOCK_SIZE) % 25, ((mapX + 16) / BLOCK_SIZE) % 25,
	                              ((mapY - 32) / BLOCK_SIZE) % 25, (mapY / BLOCK_SIZE) % 25,
                              },

                              boundaryCriteria{
	                              //左条件
	                              currentCorner[LEFT] == AREA_MAX && currentCorner[RIGHT] == AREA_MIN
	                              && currentMap.x >= currentBoundaryMap1.x && currentMap.x == currentBoundaryMap2.x,
	                              //右条件
	                              currentCorner[LEFT] == AREA_MAX && currentCorner[RIGHT] == AREA_MIN
	                              && currentMap.x == currentBoundaryMap1.x && currentMap.x <= currentBoundaryMap2.x,
	                              //上条件
	                              currentCorner[UP] == AREA_MAX && currentCorner[DOWN] == AREA_MIN
	                              && currentMap.y >= currentBoundaryMap1.y && currentMap.y == currentBoundaryMap2.y,
	                              //下条件
	                              currentCorner[UP] == AREA_MAX && currentCorner[DOWN] == AREA_MIN
	                              && currentMap.y == currentBoundaryMap1.y && currentMap.y <= currentBoundaryMap2.y,
	                              //中央横1条件
	                              currentCorner[CENTER_X1] == AREA_MAX && currentCorner[CENTER_X2] == AREA_MIN
	                              && currentMap.x >= currentBoundaryMap1.x && currentMap.x == currentBoundaryMap2.x,
	                              //中央横2条件
	                              currentCorner[CENTER_X1] == AREA_MAX && currentCorner[CENTER_X2] == AREA_MIN
	                              && currentMap.x == currentBoundaryMap1.x && currentMap.x <= currentBoundaryMap2.x,
	                              //中央縦1条件
	                              currentCorner[CENTER_Y1] == AREA_MAX && currentCorner[CENTER_Y2] == AREA_MIN
	                              && currentMap.y >= currentBoundaryMap1.y && currentMap.y == currentBoundaryMap2.y,
	                              //中央縦2条件
	                              currentCorner[CENTER_Y1] == AREA_MAX && currentCorner[CENTER_Y2] == AREA_MIN
	                              && currentMap.y == currentBoundaryMap1.y && currentMap.y <= currentBoundaryMap2.y,
	                              //境界線交差時の特殊条件
	                              currentCorner[LEFT] == AREA_MAX && currentCorner[RIGHT] == AREA_MIN
	                              && currentCorner[UP] == AREA_MAX && currentCorner[DOWN] == AREA_MIN
	                              && currentMap.x == currentBoundaryMap1.x && currentMap.y > currentBoundaryMap1.y
	                              && currentMap.x < currentBoundaryMap2.x && currentMap.y == currentBoundaryMap2.y
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
	currentBoundaryMap1.x = (mapX - 32) / (BLOCK_SIZE * mapAspectSize.x); //左端
	currentBoundaryMap1.y = (mapY - 48) / (BLOCK_SIZE * mapAspectSize.y); //上端
	currentBoundaryMap2.x = (mapX + 31) / (BLOCK_SIZE * mapAspectSize.x); //右端
	currentBoundaryMap2.y = (mapY + 15) / (BLOCK_SIZE * mapAspectSize.y); //下端
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
/// 読み込んだマップチップ画像からマップ描画
/// </summary>
/// <param name="mapInformation"></param>
/// <param name="dirX">x方向の中心からの距離</param>
/// <param name="dirY">y方向の中心からの距離</param>
/// <param name="map">マップの配列</param>
void MapDraw::drawMapChips(const int& mapInformation, const int& dirX, const int& dirY,
                           vector<vector<int>>& map) {

	mapName(&matrix.y, &matrix.x, mapInformation); //マップ情報から列と行を取り出す
	//マップチップの描画
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
void MapDraw::drawCurrentMaps(vector<vector<int>>& map, const int& dirX, const int& dirY) {
	fileImport(currentMap.x + dirX, currentMap.y + dirY, map); //csvファイル読み込み
	/*マップチップ描画*/
	for (auto i : information)
		drawMapChips(i, centerPos.x + dirX, centerPos.y + dirY, map);
}

/// <summary>
/// 更新処理
/// </summary>
void MapDraw::update() {

	/* 9か所のマップを描画 */
	drawCurrentMaps(mapCentral, Central, Central); //中央マップ（常に表示）

	//y方向のマップ描画判定
	if (blockArea.y <= TOP_BOUNDARY)
		drawCurrentMaps(mapTopCentral, Central, Top); //上マップ
	else if (blockArea.y >= BOTTOM_BOUNDARY)
		drawCurrentMaps(mapBottomCentral, Central, Bottom); //下マップ

	//x方向のマップ描画判定
	if (blockArea.x <= LEFT_BOUNDARY)
		drawCurrentMaps(mapLeftCentral, Left, Central); //左マップ
	else if (blockArea.x >= RIGHT_BOUNDARY)
		drawCurrentMaps(mapRightCentral, Right, Central); //右マップ

	//斜め方向のマップ描画判定
	if (blockArea.x <= LEFT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		drawCurrentMaps(mapTopLeft, Left, Top); //左上マップ
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		drawCurrentMaps(mapTopRight, Right, Top); //右上マップ
	else if (blockArea.x <= LEFT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		drawCurrentMaps(mapBottomLeft, Left, Bottom); //左下マップ
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		drawCurrentMaps(mapBottomRight, Right, Bottom); //右下マップ

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

	DrawFormatString(1000, 75, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapCentral[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 90, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 105, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 120, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(700, 75, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapLeftCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapLeftCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapLeftCentral[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapLeftCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 90, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapLeftCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapLeftCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 105, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapLeftCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapLeftCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 120, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapLeftCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapLeftCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapLeftCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapLeftCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(1300, 75, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapRightCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapRightCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapRightCentral[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapRightCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 90, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapRightCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapRightCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 105, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapRightCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapRightCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 120, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapRightCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapRightCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapRightCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapRightCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(700, 0, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapTopLeft[currentCorner[UP]][currentCorner[LEFT]],
	                 mapTopLeft[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapTopLeft[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapTopLeft[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 15, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapTopLeft[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapTopLeft[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 30, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapTopLeft[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapTopLeft[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 45, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapTopLeft[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapTopLeft[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapTopLeft[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapTopLeft[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(1300, 0, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapTopRight[currentCorner[UP]][currentCorner[LEFT]],
	                 mapTopRight[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapTopRight[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapTopRight[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 15, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapTopRight[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapTopRight[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 30, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapTopRight[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapTopRight[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 45, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapTopRight[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapTopRight[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapTopRight[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapTopRight[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(1000, 0, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapTopCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapTopCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapTopCentral[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapTopCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 15, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapTopCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapTopCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 30, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapTopCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapTopCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 45, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapTopCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapTopCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapTopCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapTopCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(700, 150, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapBottomLeft[currentCorner[UP]][currentCorner[LEFT]],
	                 mapBottomLeft[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapBottomLeft[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapBottomLeft[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 165, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapBottomLeft[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapBottomLeft[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 180, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapBottomLeft[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapBottomLeft[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 195, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapBottomLeft[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapBottomLeft[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapBottomLeft[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapBottomLeft[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(1300, 150, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapBottomRight[currentCorner[UP]][currentCorner[LEFT]],
	                 mapBottomRight[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapBottomRight[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapBottomRight[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 165, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapBottomRight[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapBottomRight[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 180, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapBottomRight[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapBottomRight[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 195, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapBottomRight[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapBottomRight[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapBottomRight[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapBottomRight[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(1000, 150, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapBottomCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapBottomCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapBottomCentral[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapBottomCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 165, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapBottomCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapBottomCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 180, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapBottomCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapBottomCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 195, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapBottomCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapBottomCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapBottomCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapBottomCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(150, 15, GetColor(255, 255, 255), "L:%d, R:%d, U:%d, D:%d",
	                 currentCorner[LEFT], currentCorner[RIGHT], currentCorner[UP], currentCorner[DOWN], false);
	DrawFormatString(150, 30, GetColor(255, 255, 255), "CX1:%d, CX2:%d, CY1:%d, CY2:%d",
	                 currentCorner[CENTER_X1], currentCorner[CENTER_X2], currentCorner[CENTER_Y1],
	                 currentCorner[CENTER_Y2], false);

	DrawFormatString(0, 15, GetColor(255, 255, 255), "(iniY:%d, iniX:%d)", centerPos.y, centerPos.x, false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "mX%d, mY%d", currentMap.x, currentMap.y, false);
	DrawFormatString(0, 45, GetColor(255, 255, 255), "cby1:%d, cbx1:%d, cby2:%d, cbx2:%d",
	                 currentBoundaryMap1.y, currentBoundaryMap1.x, currentBoundaryMap2.y, currentBoundaryMap2.x, false);
	DrawFormatString(0, 880, GetColor(200, 120, 0), "X%d, Y%d", mapX, mapY, false);
}

/// <summary>
/// 左上の衝突判定
/// </summary>
void MapDraw::collisionDetectionLeftUp() {
	if (boundaryCriteria[CROSS])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_TOP_LEFT, LEFT, UP)) ? true : false;
	else if (boundaryCriteria[LEFT])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, UP)) ? true : false;
	else if (boundaryCriteria[UP])
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_TOP_CENTRAL, LEFT, UP)) ? true : false;
	else
		collisionFlag[LEFT_UP] = (collisionDetection(MAP_CENTRAL, LEFT, UP)) ? true : false;
}

/// <summary>
/// 右上の衝突判定
/// </summary>
void MapDraw::collisionDetectionRightUp() {
	if (boundaryCriteria[CROSS] || boundaryCriteria[UP])
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_TOP_CENTRAL, RIGHT, UP)) ? true : false;
	else if (boundaryCriteria[RIGHT])
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, UP)) ? true : false;
	else
		collisionFlag[RIGHT_UP] = (collisionDetection(MAP_CENTRAL, RIGHT, UP)) ? true : false;
}

/// <summary>
/// 左下の衝突判定
/// </summary>
void MapDraw::collisionDetectionLeftDown() {
	if (boundaryCriteria[LEFT] || boundaryCriteria[CROSS])
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, DOWN)) ? true : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_BOTTOM_CENTRAL, LEFT, DOWN)) ? true : false;
	else
		collisionFlag[LEFT_DOWN] = (collisionDetection(MAP_CENTRAL, LEFT, DOWN)) ? true : false;
}

/// <summary>
/// 右下の衝突判定
/// </summary>
void MapDraw::collisionDetectionRightDown() {
	if (boundaryCriteria[RIGHT])
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, DOWN)) ? true : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_BOTTOM_CENTRAL, RIGHT, DOWN)) ? true : false;
	else
		collisionFlag[RIGHT_DOWN] = (collisionDetection(MAP_CENTRAL, RIGHT, DOWN)) ? true : false;
}

/// <summary>
/// 左中央1の衝突判定
/// </summary>
void MapDraw::collisionDetectionCenterLeft1() {
	if (boundaryCriteria[CENTER_Y1])
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_TOP_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
	else if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
	else
		collisionFlag[CENTER_LEFT1] = (collisionDetection(MAP_CENTRAL, LEFT, CENTER_Y1)) ? true : false;
}

/// <summary>
/// 左中央2の衝突判定
/// </summary>
void MapDraw::collisionDetectionCenterLeft2() {
	if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT2] = (collisionDetection(MAP_LEFT_CENTRAL, LEFT, CENTER_Y2)) ? true : false;
	else
		collisionFlag[CENTER_LEFT2] = (collisionDetection(MAP_CENTRAL, LEFT, CENTER_Y2)) ? true : false;
}

/// <summary>
/// 右中央1の衝突判定
/// </summary>
void MapDraw::collisionDetectionCenterRight1() {
	if (boundaryCriteria[CENTER_Y1])
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_TOP_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
	else if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
	else
		collisionFlag[CENTER_RIGHT1] = (collisionDetection(MAP_CENTRAL, RIGHT, CENTER_Y1)) ? true : false;
}

/// <summary>
/// 右中央2の衝突判定
/// </summary>
void MapDraw::collisionDetectionCenterRight2() {
	if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT2] = (collisionDetection(MAP_RIGHT_CENTRAL, RIGHT, CENTER_Y2)) ? true : false;
	else
		collisionFlag[CENTER_RIGHT2] = (collisionDetection(MAP_CENTRAL, RIGHT, CENTER_Y2)) ? true : false;
}

/// <summary>
/// 上中央1の衝突判定
/// </summary>
void MapDraw::collisionDetectionCenterUp1() {
	if (boundaryCriteria[CENTER_X1])
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_LEFT_CENTRAL, CENTER_X1, UP)) ? true : false;
	else if (boundaryCriteria[UP])
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_TOP_CENTRAL, CENTER_X1, UP)) ? true : false;
	else
		collisionFlag[CENTER_UP1] = (collisionDetection(MAP_CENTRAL, CENTER_X1, UP)) ? true : false;
}

/// <summary>
/// 上中央2の衝突判定
/// </summary>
void MapDraw::collisionDetectionCenterUp2() {
	if (boundaryCriteria[CENTER_X2])
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_RIGHT_CENTRAL, CENTER_X2, UP)) ? true : false;
	else if (boundaryCriteria[UP])
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_TOP_CENTRAL, CENTER_X2, UP)) ? true : false;
	else
		collisionFlag[CENTER_UP2] = (collisionDetection(MAP_CENTRAL, CENTER_X2, UP)) ? true : false;
}

/// <summary>
/// 下中央1の衝突判定
/// </summary>
void MapDraw::collisionDetectionCenterDown1() {
	if (boundaryCriteria[CENTER_X1])
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_LEFT_CENTRAL, CENTER_X1, DOWN)) ? true : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_BOTTOM_CENTRAL, CENTER_X1, DOWN)) ? true : false;
	else
		collisionFlag[CENTER_DOWN1] = (collisionDetection(MAP_CENTRAL, CENTER_X1, DOWN)) ? true : false;
}

/// <summary>
/// 下中央2の衝突判定
/// </summary>
void MapDraw::collisionDetectionCenterDown2() {
	if (boundaryCriteria[CENTER_X2])
		collisionFlag[CENTER_DOWN2] = (collisionDetection(MAP_RIGHT_CENTRAL, CENTER_X2, DOWN)) ? true : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[CENTER_DOWN2] = (collisionDetection(MAP_BOTTOM_CENTRAL, CENTER_X2, DOWN)) ? true : false;
	else
		collisionFlag[CENTER_DOWN2] = (collisionDetection(MAP_CENTRAL, CENTER_X2, DOWN)) ? true : false;
}

/// <summary>
/// 判定を行うマップとそのマップの座標の組み合わせで衝突判定をとる
/// 結果をbool値で返す
/// </summary>
/// <param name="dirXY">判定を行うマップ名</param>
/// <param name="dirX">判定対象のx座標</param>
/// <param name="dirY">判定対象のy座標</param>
bool MapDraw::collisionDetection(const int& dirXY, const int& dirX, const int& dirY) {
	switch (dirXY) {
	case MAP_TOP_LEFT:
		return mapTopLeft[currentCorner[dirY]][currentCorner[dirX]] > MOVE_RANGE;
	case MAP_TOP_CENTRAL:
		return mapTopCentral[currentCorner[dirY]][currentCorner[dirX]] > MOVE_RANGE;
	case MAP_TOP_RIGHT:
		return mapTopRight[currentCorner[dirY]][currentCorner[dirX]] > MOVE_RANGE;
	case MAP_LEFT_CENTRAL:
		return mapLeftCentral[currentCorner[dirY]][currentCorner[dirX]] > MOVE_RANGE;
	case MAP_CENTRAL:
		return mapCentral[currentCorner[dirY]][currentCorner[dirX]] > MOVE_RANGE;
	case MAP_RIGHT_CENTRAL:
		return mapRightCentral[currentCorner[dirY]][currentCorner[dirX]] > MOVE_RANGE;
	case MAP_BOTTOM_LEFT:
		return mapBottomLeft[currentCorner[dirY]][currentCorner[dirX]] > MOVE_RANGE;
	case MAP_BOTTOM_CENTRAL:
		return mapBottomCentral[currentCorner[dirY]][currentCorner[dirX]] > MOVE_RANGE;
	case MAP_BOTTOM_RIGHT:
		return mapBottomRight[currentCorner[dirY]][currentCorner[dirX]] > MOVE_RANGE;
	default:
		return false;
	}
}
