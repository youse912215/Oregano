#pragma once
#include "mapBase.h"
#include <vector>

using namespace std;

class MapDraw : public MapBase {
private:
	int map_graph; //マップチップ画像
	int column; //行番号
	int row; //列番号
	int widthBlockArea;
	int heightBlockArea;

	int current_map_x;
	int current_map_y;
	int map_width; //1マップあたりの配列の横サイズ
	int map_height; //1マップあたりの配列の縦サイズ]
	int sx;
	int sy;

	vector<int> info;
	vector<vector<int>> map_top_left;
	vector<vector<int>> map_top_central;
	vector<vector<int>> map_top_right;
	vector<vector<int>> map_left_central;
	vector<vector<int>> map_central;
	vector<vector<int>> map_right_central;
	vector<vector<int>> map_bottom_left;
	vector<vector<int>> map_bottom_central;
	vector<vector<int>> map_bottom_right;

	vector<int> currentCorner;

	enum BOUNDARY {
		LEFT_BOUNDARY = 12,
		RIGHT_BOUNDARY = 13,
		TOP_BOUNDARY = 7,
		BOTTOM_BOUNDARY = 17
	};

	void drawing_current_maps(vector<vector<int>>& map, const int& dir_x, const int& dir_y);

public:
	static int map_x;
	static int map_y;
	int screen_x; //画面上のx座標
	int screen_y; //画面上のy座標
	int map_between_distance; //マップ間距離（800px）
	vector<int> collisionFlag; //衝突フラグ

	void current_map_drawing(const int& map_info, const int& dis_x, const int& dis_y,
	                         vector<vector<int>>& map);

	MapDraw(int graph);
	~MapDraw();
	void update();
	void get_player_coodinate(const int& x, const int& y);
	void collisionDetection();
};
