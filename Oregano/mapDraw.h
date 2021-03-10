#pragma once
#include "mapBase.h"
#include "dataSource.h"
#include "vec2.h"
#include <vector>

using namespace std;

class MapDraw : public MapBase {
private:
	DataSource source_;
	int mapBetweenDistance; //マップ間距離（1600px）

	Vec2 screen; //画面上の座標

	Vec2 mapAspectSize; //1マップあたりの配列のサイズ
	Vec2 centerPos; //マップの中央位置

	const int informationSize; //マップ情報数

	/* 各方向の境界 */
	enum BOUNDARY {
		//左
		LEFT_BOUNDARY = 12,
		//右
		RIGHT_BOUNDARY = 13,
		//上
		TOP_BOUNDARY = 7,
		//下
		BOTTOM_BOUNDARY = 17
	};

	//中心からの1マップあたりの距離によって、現在のマップを描画し、マップ配列を返す
	vector<vector<int>> drawCurrentMaps(const int& dirX, const int& dirY,
	                                    vector<vector<vector<int>>>& mapAll);
	//読み込んだマップチップ情報からマップを描画する
	void drawMapChips(const int& mapInformation, const int& dirX, const int& dirY,
	                  vector<vector<int>>& map);

	int matrixX(const int& mapInfo); //マップ情報から行を取り出す
	int matrixY(const int& mapInfo); //マップ情報から列を取り出す

public:
	static int mapX; //マップ内の中央のx座標
	static int mapY; //マップ内の中央のy座標

	Vec2 blockArea; //1ブロック区画（マップ）内の座標

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

	MapDraw();
	~MapDraw();

	void initialize(); //初期化

	void update(vector<vector<vector<int>>>& mapAll); //更新処理
};
