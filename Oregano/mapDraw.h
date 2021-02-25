#pragma once
#include "mapBase.h"
#include "vec2.h"
#include <vector>

using namespace std;

class MapDraw : public MapBase {
private:
	int graph; //マップ画像
	int mapBetweenDistance; //マップ間距離（1600px）

	Vec2 matrix; //行列番号
	Vec2 screen; //画面上の座標
	Vec2 blockArea; //1ブロック区画（マップ）内の座標
	Vec2 mapAspectSize; //1マップあたりの配列のサイズ
	Vec2 centerPos; //マップの中央位置

	vector<int> information; //マップ名情報

	enum BOUNDARY {
		//各境界
		LEFT_BOUNDARY = 12,
		RIGHT_BOUNDARY = 13,
		TOP_BOUNDARY = 7,
		BOTTOM_BOUNDARY = 17
	};

	void drawCurrentMaps(vector<vector<int>>& map, const int& dirX, const int& dirY);
	void drawMapChips(const int& mapInformation, const int& dirX, const int& dirY,
	                  vector<vector<int>>& map);
	void mapName(int* column, int* row, const int& mapInfo);
public:
	static int mapX; //マップ内の中央のx座標
	static int mapY; //マップ内の中央のy座標

	Vec2 currentMap; //現在のマップ座標
	Vec2 currentBoundaryMap1; //現在のマップの境界座標
	Vec2 currentBoundaryMap2; //現在のマップの境界座標

	vector<int> currentCorner; //現在の各角のマップ座標（中央も含む）
	vector<vector<int>> mapTopLeft; //左上マップ
	vector<vector<int>> mapTopCentral; //上マップ
	vector<vector<int>> mapTopRight; //右上マップ
	vector<vector<int>> mapLeftCentral; //左マップ
	vector<vector<int>> mapCentral; //中央マップ
	vector<vector<int>> mapRightCentral; //右上マップ
	vector<vector<int>> mapBottomLeft; //左下マップ
	vector<vector<int>> mapBottomCentral; //下マップ
	vector<vector<int>> mapBottomRight; //右下マップ

	MapDraw(int graph);
	~MapDraw();
	void update();
};
