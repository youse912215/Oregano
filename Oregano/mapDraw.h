#pragma once
#include "mapBase.h"
#include <vector>

using namespace std;

class MapDraw : public MapBase {
private:
	int map_graph; //�}�b�v�`�b�v�摜
	int column; //�s�ԍ�
	int row; //��ԍ�
	int widthBlockArea;
	int heightBlockArea;

	int current_map_x;
	int current_map_y;
	int map_width; //1�}�b�v������̔z��̉��T�C�Y
	int map_height; //1�}�b�v������̔z��̏c�T�C�Y]
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
	int screen_x; //��ʏ��x���W
	int screen_y; //��ʏ��y���W
	int map_between_distance; //�}�b�v�ԋ����i800px�j
	vector<int> collisionFlag; //�Փ˃t���O

	void current_map_drawing(const int& map_info, const int& dis_x, const int& dis_y,
	                         vector<vector<int>>& map);

	MapDraw(int graph);
	~MapDraw();
	void update();
	void get_player_coodinate(const int& x, const int& y);
	void collisionDetection();
};
