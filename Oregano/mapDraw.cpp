#include "mapDraw.h"
#include "coordinate_confirmation.h"
#include "mapInformation.h"
#include "DxLib.h"

int MapDraw::map_x = INITIAL_X; //x����
int MapDraw::map_y = INITIAL_Y; //y����

MapDraw::MapDraw(int graph) : map_graph(graph),
                              info{FLOOR, HOUSE, SHALLOW, TIDE, WATER, STONE, WOODS},
                              map_top_left(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              map_top_central(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              map_top_right(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              map_left_central(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              map_central(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              map_right_central(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              map_bottom_left(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              map_bottom_central(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              map_bottom_right(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              currentCorner{
	                              ((map_x - 32) / BLOCK_SIZE) % 25, ((map_x + 31) / BLOCK_SIZE) % 25,
	                              ((map_y - 48) / BLOCK_SIZE) % 25, ((map_y + 15) / BLOCK_SIZE) % 25,
	                              (map_x / BLOCK_SIZE) % 25, ((map_y - 16) / BLOCK_SIZE) % 25,
                              },
                              collisionFlag(8) {
	column = 0; //��
	row = 0; //�s
	screen_x = INITIAL_X - map_x; //��ʏ��x���W
	screen_y = INITIAL_Y - map_y; //��ʏ��y���W
	map_width = map_all.at(0).size(); //���̃T�C�Y
	map_height = map_all.size(); //�c�̃T�C�Y
	current_map_x = map_x / (BLOCK_SIZE * map_width); //���݂̑S�̃}�b�v��x���W
	current_map_y = map_y / (BLOCK_SIZE * map_height); //���݂̑S�̃}�b�v��y���W
	sx = current_map_x - 8;
	sy = current_map_y - 8;
	map_between_distance = BLOCK_SIZE * AREA_WIDTH; //�}�b�v�ԋ����i800px�j
	widthBlockArea = (map_x / BLOCK_SIZE) % AREA_WIDTH;
	heightBlockArea = (map_y / BLOCK_SIZE) % AREA_HEIGHT;
}

MapDraw::~MapDraw() {
}


//---  ���݃}�b�v�Ə㉺���E�΂߂̍��v9�}�b�v��`��@---//

/// <summary>
/// �ǂݍ��񂾃}�b�v�ɕ`�悷��
/// </summary>
/// <param name="map_info"></param>
/// <param name="dis_x">x�����̒��S����̋���</param>
/// <param name="dis_y">y�����̒��S����̋���</param>
/// <param name="map_xy">�}�b�v�̔z��</param>
void MapDraw::current_map_drawing(const int& map_info, const int& dis_x, const int& dis_y,
                                  vector<vector<int>>& map) {

	mapName(&column, &row, map_info); //�}�b�v��񂩂��ƍs�����o��
	//�}�b�v�̕`��
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			//map_info�̃`�b�v��dest�̈ʒu�ɕ`��
			if (map[y][x] == map_info) {
				DrawRectGraph(
					x * BLOCK_SIZE + screen_x + map_between_distance * dis_x,
					y * BLOCK_SIZE + screen_y + map_between_distance * dis_y,
					column * BLOCK_SIZE, row * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE,
					map_graph, true, false);
			}
		}
	}
}

void MapDraw::drawing_current_maps(vector<vector<int>>& map, const int& dir_x, const int& dir_y) {
	file_import(current_map_x + dir_x, current_map_y + dir_y, map); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(FLOOR, sx + dir_x, sy + dir_y, map);
	current_map_drawing(HOUSE, sx + dir_x, sy + dir_y, map);
	current_map_drawing(SHALLOW, sx + dir_x, sy + dir_y, map);
	current_map_drawing(WATER, sx + dir_x, sy + dir_y, map);
	current_map_drawing(WOODS, sx + dir_x, sy + dir_y, map);
	//---------------------//
}

/// <summary>
/// 9�}�b�v�̕`��
/// </summary>
void MapDraw::update() {

	drawing_current_maps(map_central, Central, Central);

	if (heightBlockArea <= TOP_BOUNDARY)
		drawing_current_maps(map_top_central, Central, Top);
	else if (heightBlockArea >= BOTTOM_BOUNDARY)
		drawing_current_maps(map_bottom_central, Central, Bottom);


	if (widthBlockArea <= LEFT_BOUNDARY)
		drawing_current_maps(map_left_central, Left, Central);
	else if (widthBlockArea >= RIGHT_BOUNDARY)
		drawing_current_maps(map_right_central, Right, Central);


	if (widthBlockArea <= LEFT_BOUNDARY && heightBlockArea <= TOP_BOUNDARY)
		drawing_current_maps(map_top_left, Left, Top);
	else if (widthBlockArea >= RIGHT_BOUNDARY && heightBlockArea <= TOP_BOUNDARY)
		drawing_current_maps(map_top_right, Right, Top);
	else if (widthBlockArea <= LEFT_BOUNDARY && heightBlockArea >= BOTTOM_BOUNDARY)
		drawing_current_maps(map_bottom_left, Left, Bottom);
	else if (widthBlockArea >= RIGHT_BOUNDARY && heightBlockArea >= BOTTOM_BOUNDARY)
		drawing_current_maps(map_bottom_right, Right, Bottom);

	DrawFormatString(150, 0, GetColor(255, 255, 255), "LU:%d, RU:%d",
	                 map_central[currentCorner[UP]][currentCorner[LEFT]],
	                 map_central[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(300, 0, GetColor(255, 255, 255), "LD:%d, RD:%d",
	                 map_central[currentCorner[DOWN]][currentCorner[LEFT]],
	                 map_central[currentCorner[DOWN]][currentCorner[RIGHT]], false);
	DrawFormatString(450, 0, GetColor(255, 255, 255), "LU:%d, RU:%d, LD:%d, RD:%d",
	                 collisionFlag[0], collisionFlag[1], collisionFlag[2], collisionFlag[3], false);

	DrawFormatString(150, 15, GetColor(255, 255, 255),
	                 "(cy:%d, cx:%d)", (map_y / BLOCK_SIZE) % 25, (map_x / BLOCK_SIZE) % 25, false);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "(sy:%d, sx:%d)", sy, sx, false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d, %d", current_map_y, current_map_x, false);
}

void MapDraw::collisionDetection() {
	if (map_central[currentCorner[UP]][currentCorner[LEFT]] == WOODS) {
		collisionFlag[LEFT_UP] = 1;
	}
	else {
		collisionFlag[LEFT_UP] = 0;
	}

	if (map_central[currentCorner[UP]][currentCorner[RIGHT]] == WOODS) {
		collisionFlag[RIGHT_UP] = 1;
	}
	else {
		collisionFlag[RIGHT_UP] = 0;
	}

	if (map_central[currentCorner[DOWN]][currentCorner[LEFT]] == WOODS) {
		collisionFlag[LEFT_DOWN] = 1;
	}
	else {
		collisionFlag[LEFT_DOWN] = 0;
	}

	if (map_central[currentCorner[DOWN]][currentCorner[RIGHT]] == WOODS) {
		collisionFlag[RIGHT_DOWN] = 1;
	}
	else {
		collisionFlag[RIGHT_DOWN] = 0;
	}


	if (map_central[currentCorner[CENTER_Y]][currentCorner[LEFT]] == WOODS) {
		collisionFlag[CENTER_LEFT] = 1;
	}
	else {
		collisionFlag[CENTER_LEFT] = 0;
	}

	if (map_central[currentCorner[CENTER_Y]][currentCorner[RIGHT]] == WOODS) {
		collisionFlag[CENTER_RIGHT] = 1;
	}
	else {
		collisionFlag[CENTER_RIGHT] = 0;
	}

	if (map_central[currentCorner[UP]][currentCorner[CENTER_X]] == WOODS) {
		collisionFlag[CENTER_UP] = 1;
	}
	else {
		collisionFlag[CENTER_UP] = 0;
	}

	if (map_central[currentCorner[DOWN]][currentCorner[CENTER_X]] == WOODS) {
		collisionFlag[CENTER_DOWN] = 1;
	}
	else {
		collisionFlag[CENTER_DOWN] = 0;
	}
}
