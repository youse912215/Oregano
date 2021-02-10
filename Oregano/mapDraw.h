#pragma once
#include "mapBase.h"
#include <vector>

using namespace std;

class MapDraw : public MapBase {
private:
	int graph; //マップチップ画像
	int column; //行番号
	int row; //列番号
	int blockAreaX; //1ブロック区画（マップ）内のx座標
	int blockAreaY; //1ブロック区画（マップ）内のy座標

	int currentMapX;
	int currentMapY;
	int mapWidth; //1マップあたりの配列の横サイズ
	int mapHeight; //1マップあたりの配列の縦サイズ]
	int initialX; //
	int initialY;

	vector<int> info; //マップ名情報

	vector<vector<int>> mapTopLeft; //左上マップ
	vector<vector<int>> mapTopCentral; //上マップ
	vector<vector<int>> mapTopRight; //右上マップ
	vector<vector<int>> mapLeftCentral; //左マップ
	vector<vector<int>> mapCentral; //中央マップ
	vector<vector<int>> mapRightCentral; //右上マップ
	vector<vector<int>> mapBottomLeft; //左下マップ
	vector<vector<int>> mapBottomCentral; //下マップ
	vector<vector<int>> mapBottomRight; //右下マップ

	vector<int> currentCorner; //現在の各角のマップ座標（中央も含む）

	enum BOUNDARY {
		//各境界
		LEFT_BOUNDARY = 12,
		RIGHT_BOUNDARY = 13,
		TOP_BOUNDARY = 7,
		BOTTOM_BOUNDARY = 17
	};

	void drawing_current_maps(vector<vector<int>>& map, const int& dirX, const int& dirY);
	void current_map_drawing(const int& map_info, const int& dirX, const int& dirY,
	                         vector<vector<int>>& map);
	void collisionDetection(const int& x, const int& y, const int& direction);

public:
	static int mapX; //マップ内の中央のx座標
	static int mapY; //マップ内の中央のy座標
	int screenX; //画面上のx座標
	int screenY; //画面上のy座標
	int mapBetweenDistance; //マップ間距離（800px）
	vector<bool> collisionFlag; //衝突フラグ

	MapDraw(int graph);
	~MapDraw();
	void update();
};
