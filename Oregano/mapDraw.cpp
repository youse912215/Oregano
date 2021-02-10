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
	                              (mapX / BLOCK_SIZE) % 25, ((mapY - 16) / BLOCK_SIZE) % 25,
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
                              collisionFlag(8) {
	//column = 0; //列
	//row = 0; //行
	matrix.x = 0;
	matrix.y = 0;
	screen.x = INITIAL_X - mapX; //画面上のx座標
	screen.y = INITIAL_Y - mapY; //画面上のy座標
	mapAspectSize.x = mapBase.at(0).size(); //横のサイズ
	mapAspectSize.y = mapBase.size(); //縦のサイズ
	currentMap.x = mapX / (BLOCK_SIZE * mapAspectSize.x); //現在の全体マップのx座標
	currentMap.y = mapY / (BLOCK_SIZE * mapAspectSize.y); //現在の全体マップのy座標
	centerPos.x = currentMap.x - 8;
	centerPos.y = currentMap.y - 8;
	mapBetweenDistance = BLOCK_SIZE * AREA_WIDTH; //マップ間距離（800px）
	blockArea.x = (mapX / BLOCK_SIZE) % AREA_WIDTH;
	blockArea.y = (mapY / BLOCK_SIZE) % AREA_HEIGHT;
}

MapDraw::~MapDraw() {
}

/// <summary>
/// 読み込んだマップに描画する
/// </summary>
/// <param name="map_info"></param>
/// <param name="dirX">x方向の中心からの距離</param>
/// <param name="dirY">y方向の中心からの距離</param>
/// <param name="map">マップの配列</param>
void MapDraw::current_map_drawing(const int& map_info, const int& dirX, const int& dirY,
                                  vector<vector<int>>& map) {

	mapName(&matrix.y, &matrix.x, map_info); //マップ情報から列と行を取り出す
	//マップの描画
	for (int y = 0; y < mapAspectSize.y; y++) {
		for (int x = 0; x < mapAspectSize.x; x++) {
			//map_infoのチップをdestの位置に描画
			if (map[y][x] == map_info) {
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

	/* 8ヵ所の衝突判定 */
	collisionDetection(LEFT, UP, LEFT_UP); //左上
	collisionDetection(RIGHT, UP, RIGHT_UP); //右上
	collisionDetection(LEFT, DOWN, LEFT_DOWN); //左下
	collisionDetection(RIGHT, DOWN, RIGHT_DOWN); //右下
	collisionDetection(LEFT, CENTER_Y, CENTER_LEFT); //中央左
	collisionDetection(RIGHT, CENTER_Y, CENTER_RIGHT); //中央右
	collisionDetection(CENTER_X, UP, CENTER_UP); //中央上
	collisionDetection(CENTER_X, DOWN, CENTER_DOWN); //中央下

	DrawFormatString(150, 0, GetColor(255, 255, 255), "LU:%d, RU:%d",
	                 mapCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(300, 0, GetColor(255, 255, 255), "LD:%d, RD:%d",
	                 mapCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);
	DrawFormatString(150, 15, GetColor(255, 255, 255),
	                 "(cy:%d, cx:%d)", (mapY / BLOCK_SIZE) % 25, (mapX / BLOCK_SIZE) % 25, false);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "(iniY:%d, iniX:%d)", centerPos.y, centerPos.x, false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d, %d", currentMap.y, currentMap.x, false);
}

bool MapDraw::leftCollisionFlag() {
	return (collisionFlag[LEFT_UP] || collisionFlag[LEFT_DOWN]) && collisionFlag[CENTER_LEFT];
}

bool MapDraw::rightCollisionFlag() {
	return (collisionFlag[RIGHT_UP] || collisionFlag[RIGHT_DOWN]) && collisionFlag[CENTER_RIGHT];
}

bool MapDraw::upCollisionFlag() {
	return (collisionFlag[LEFT_UP] || collisionFlag[RIGHT_UP]) && collisionFlag[CENTER_UP];
}

bool MapDraw::downCollisionFlag() {
	return (collisionFlag[LEFT_DOWN] || collisionFlag[RIGHT_DOWN]) && collisionFlag[CENTER_DOWN];
}

/// <summary>
/// 指定した位置の衝突判定を得る
/// </summary>
/// <param name="x">x軸の方向</param>
/// <param name="y">y軸の方向</param>
/// <param name="direction">判定方向</param>
void MapDraw::collisionDetection(const int& x, const int& y, const int& direction) {
	collisionFlag[direction] = (mapCentral[currentCorner[y]][currentCorner[x]] == WOODS) ? true : false;
}
