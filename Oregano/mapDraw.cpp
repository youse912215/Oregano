#include "mapDraw.h"
#include "DxLib.h"

int MapDraw::mapX = INITIAL_X; //x方向
int MapDraw::mapY = INITIAL_Y; //y方向

MapDraw::MapDraw() : informationSize(15),

                     /* 各角のマップ座標 */
                     currentCorner(8),

                     /* 9か所のマップ配列 */
                     mapTopLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapTopCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapTopRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapLeftCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapRightCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapBottomLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapBottomCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapBottomRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)) {
}

MapDraw::~MapDraw() {
}

void MapDraw::initialize() {
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

	currentCorner = {
			((mapX - 32) / BLOCK_SIZE) % AREA_WIDTH, ((mapX + 31) / BLOCK_SIZE) % AREA_WIDTH,
			((mapY - 48) / BLOCK_SIZE) % AREA_HEIGHT, ((mapY + 15) / BLOCK_SIZE) % AREA_HEIGHT,
			((mapX - 16) / BLOCK_SIZE) % AREA_WIDTH, ((mapX + 16) / BLOCK_SIZE) % AREA_WIDTH,
			((mapY - 32) / BLOCK_SIZE) % AREA_HEIGHT, (mapY / BLOCK_SIZE) % AREA_HEIGHT,
		};
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
				source_.mapChip, true, false);
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
vector<vector<int>> MapDraw::drawCurrentMaps(const int& dirX, const int& dirY,
                                             vector<vector<vector<int>>>& mapAll) {
	/*マップチップの描画*/
	for (auto i = 0; i < informationSize; ++i) //マップ情報（名称）の数だけ繰り返す
		drawMapChips(i, centerPos.x + dirX, centerPos.y + dirY,
		             mapAll[(currentMap.x + dirX) + (currentMap.y + dirY) * TOTAL_MAPS_Y]);

	return mapAll[(currentMap.x + dirX) + (currentMap.y + dirY) * TOTAL_MAPS_Y]; //距離に応じたマップを返す
}

/// <summary>
/// 更新処理
/// </summary>
void MapDraw::update(vector<vector<vector<int>>>& mapAll) {
	initialize();

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
}
