#include "mapDraw.h"
#include "DxLib.h"

int MapDraw::mapX = INITIAL_X; //x方向
int MapDraw::mapY = INITIAL_Y; //y方向

MapDraw::MapDraw(int graph) : graph(graph),

                              information{
	                              //花床
	                              FLOOR_FLOWER,
	                              //宝箱の床
	                              FLOOR_TREASURE,
	                              //床（通常道）
	                              FLOOR_NORMAL,
	                              //花1
	                              FLOWER1,
	                              //花2
	                              FLOWER2,
	                              //でこぼこ
	                              ROUGH,
	                              //浅瀬
	                              SHALLOW,
	                              //水沼
	                              SWAMP,
	                              //毒沼
	                              POISON,
	                              //氷床
	                              ICE,
	                              //ランダムマップ(森)
	                              RANDOM_MAP1,
	                              //ランダムマップ2(沼地)
	                              RANDOM_MAP2,
	                              //壁
	                              WALL,
	                              //外海
	                              SEA,
	                              //宝箱
	                              TREASURE_BOX,
                              },

                              currentCorner{
	                              ((mapX - 32) / BLOCK_SIZE) % AREA_WIDTH, ((mapX + 31) / BLOCK_SIZE) % AREA_WIDTH,
	                              ((mapY - 48) / BLOCK_SIZE) % AREA_HEIGHT, ((mapY + 15) / BLOCK_SIZE) % AREA_HEIGHT,
	                              ((mapX - 16) / BLOCK_SIZE) % AREA_WIDTH, ((mapX + 16) / BLOCK_SIZE) % AREA_WIDTH,
	                              ((mapY - 32) / BLOCK_SIZE) % AREA_HEIGHT, (mapY / BLOCK_SIZE) % AREA_HEIGHT,
                              },

                              mapTopLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapTopCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapTopRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapLeftCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapRightCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)) {
	/* 画面上の座標 */
	screen.x = INITIAL_X - mapX;
	screen.y = INITIAL_Y - mapY;
	/* 1マップあたりの配列サイズ */
	mapAspectSize.x = mapCentral.at(0).size();
	mapAspectSize.y = mapCentral.size();
	/* 現在のマップ座標 */
	currentMap.x = mapX / (BLOCK_SIZE * mapAspectSize.x);
	currentMap.y = mapY / (BLOCK_SIZE * mapAspectSize.y);
	/* 現在のマップの境界座標 */
	currentBoundaryMap1.x = (mapX - HALF_BLOCK_SIZE) / (BLOCK_SIZE * mapAspectSize.x); //左端
	currentBoundaryMap1.y = (mapY - BLOCK_SIZE - QUARTER_BLOCK_SIZE) / (BLOCK_SIZE * mapAspectSize.y); //上端
	currentBoundaryMap2.x = (mapX + HALF_BLOCK_SIZE - 1) / (BLOCK_SIZE * mapAspectSize.x); //右端
	currentBoundaryMap2.y = (mapY + QUARTER_BLOCK_SIZE - 1) / (BLOCK_SIZE * mapAspectSize.y); //下端
	/* マップの中央位置 */
	centerPos.x = currentMap.x - (TOTAL_MAPS_X - 1);
	centerPos.y = currentMap.y - (TOTAL_MAPS_Y - 1);
	/* マップ間距離（1600px） */
	mapBetweenDistance = BLOCK_SIZE * AREA_WIDTH;
	/* 1ブロック区画（マップ）内の座標 */
	blockArea.x = (mapX / BLOCK_SIZE) % AREA_WIDTH;
	blockArea.y = (mapY / BLOCK_SIZE) % AREA_HEIGHT;
}

MapDraw::~MapDraw() {
}

/// <summary>
/// 読み込んだマップチップ画像からマップ描画する
/// </summary>
/// <param name="mapInformation"></param>
/// <param name="dirX">x方向の中心からの距離</param>
/// <param name="dirY">y方向の中心からの距離</param>
/// <param name="map">マップの配列</param>
void MapDraw::drawMapChips(const int& mapInformation, const int& dirX, const int& dirY,
                           vector<vector<int>>& map) {
	//マップチップの描画
	for (int y = 0; y < mapAspectSize.y; ++y) {
		for (int x = 0; x < mapAspectSize.x; ++x) {
			//mapInformationのチップをDestの位置に描画
			if (map[y][x] != mapInformation) continue; //条件以外のとき、処理をスキップする
			DrawRectGraph(
				x * BLOCK_SIZE + screen.x + mapBetweenDistance * dirX,
				y * BLOCK_SIZE + screen.y + mapBetweenDistance * dirY,
				matrixX(mapInformation) * BLOCK_SIZE,
				matrixY(mapInformation) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE,
				graph, true, false);
		}
	}
}

/// <summary>
/// マップ情報から行を取り出す
/// </summary>
/// <param name="mapInfo">マップの情報</param>
int MapDraw::matrixX(const int& mapInfo) {
	return mapInfo % 10;
}

/// <summary>
/// マップ情報から列を取り出す
/// </summary>
/// <param name="mapInfo">マップの情報</param>
int MapDraw::matrixY(const int& mapInfo) {
	return mapInfo / 10;
}

/// <summary>
/// 中心からの1マップあたりの距離によって、現在のマップを描画し、マップ配列を返す
/// </summary>
/// <param name="dirX">中心からの1マップあたりの距離（x方向）</param>
/// <param name="dirY">中心からの1マップあたりの距離（y方向）</param>
/// <param name="mapAll">全てのマップを格納した配列</param>
/// <returns></returns>
vector<vector<int>> MapDraw::drawCurrentMaps(const int& dirX, const int& dirY,
                                             vector<vector<vector<int>>>& mapAll) {
	/*マップチップの描画*/
	for (auto i : information) //マップ情報（名称）の数だけ繰り返す
		drawMapChips(i, centerPos.x + dirX, centerPos.y + dirY,
		             mapAll[(currentMap.x + dirX) + (currentMap.y + dirY) * TOTAL_MAPS_Y]);

	return mapAll[(currentMap.x + dirX) + (currentMap.y + dirY) * TOTAL_MAPS_Y]; //距離に応じたマップを返す
}

/// <summary>
/// 更新処理
/// </summary>
void MapDraw::update(vector<vector<vector<int>>>& mapAll) {

	/* 9か所のマップを描画 */
	mapCentral = drawCurrentMaps(Central, Central, mapAll); //中央マップ（常に表示）

	//y方向のマップ描画判定
	if (blockArea.y <= TOP_BOUNDARY)
		mapTopCentral = drawCurrentMaps(Central, Top, mapAll); //上マップ
	else if (blockArea.y >= BOTTOM_BOUNDARY)
		mapBottomCentral = drawCurrentMaps(Central, Bottom, mapAll); //下マップ

	//x方向のマップ描画判定
	if (blockArea.x <= LEFT_BOUNDARY)
		mapLeftCentral = drawCurrentMaps(Left, Central, mapAll); //左マップ
	else if (blockArea.x >= RIGHT_BOUNDARY)
		mapRightCentral = drawCurrentMaps(Right, Central, mapAll); //右マップ

	//斜め方向のマップ描画判定
	if (blockArea.x <= LEFT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		mapTopLeft = drawCurrentMaps(Left, Top, mapAll); //左上マップ
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		mapTopRight = drawCurrentMaps(Right, Top, mapAll); //右上マップ
	else if (blockArea.x <= LEFT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		mapBottomLeft = drawCurrentMaps(Left, Bottom, mapAll); //左下マップ
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		mapBottomRight = drawCurrentMaps(Right, Bottom, mapAll); //右下マップ


	/*DrawFormatString(1000, 75, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
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
	                 mapBottomCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);*/

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

	DrawFormatString(0, 60, GetColor(255, 255, 255), "screenX:%d, screenY:%d",
	                 1 * BLOCK_SIZE + screen.x + mapBetweenDistance * centerPos.x,
	                 1 * BLOCK_SIZE + screen.y + mapBetweenDistance * centerPos.y, false);
}
