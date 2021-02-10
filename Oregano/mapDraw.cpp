#include "mapDraw.h"
#include "coordinate_confirmation.h"
#include "mapInformation.h"
#include "DxLib.h"

int MapDraw::mapX = INITIAL_X; //x����
int MapDraw::mapY = INITIAL_Y; //y����

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
	//column = 0; //��
	//row = 0; //�s
	matrix.x = 0;
	matrix.y = 0;
	screen.x = INITIAL_X - mapX; //��ʏ��x���W
	screen.y = INITIAL_Y - mapY; //��ʏ��y���W
	mapAspectSize.x = mapBase.at(0).size(); //���̃T�C�Y
	mapAspectSize.y = mapBase.size(); //�c�̃T�C�Y
	currentMap.x = mapX / (BLOCK_SIZE * mapAspectSize.x); //���݂̑S�̃}�b�v��x���W
	currentMap.y = mapY / (BLOCK_SIZE * mapAspectSize.y); //���݂̑S�̃}�b�v��y���W
	centerPos.x = currentMap.x - 8;
	centerPos.y = currentMap.y - 8;
	mapBetweenDistance = BLOCK_SIZE * AREA_WIDTH; //�}�b�v�ԋ����i800px�j
	blockArea.x = (mapX / BLOCK_SIZE) % AREA_WIDTH;
	blockArea.y = (mapY / BLOCK_SIZE) % AREA_HEIGHT;
}

MapDraw::~MapDraw() {
}

/// <summary>
/// �ǂݍ��񂾃}�b�v�ɕ`�悷��
/// </summary>
/// <param name="map_info"></param>
/// <param name="dirX">x�����̒��S����̋���</param>
/// <param name="dirY">y�����̒��S����̋���</param>
/// <param name="map">�}�b�v�̔z��</param>
void MapDraw::current_map_drawing(const int& map_info, const int& dirX, const int& dirY,
                                  vector<vector<int>>& map) {

	mapName(&matrix.y, &matrix.x, map_info); //�}�b�v��񂩂��ƍs�����o��
	//�}�b�v�̕`��
	for (int y = 0; y < mapAspectSize.y; y++) {
		for (int x = 0; x < mapAspectSize.x; x++) {
			//map_info�̃`�b�v��dest�̈ʒu�ɕ`��
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
/// �}�b�v�����ɂ�錻�݃}�b�v�̕`��
/// </summary>
void MapDraw::drawing_current_maps(vector<vector<int>>& map, const int& dirX, const int& dirY) {
	fileImport(currentMap.x + dirX, currentMap.y + dirY, map); //csv�t�@�C���ǂݍ���
	/*�}�b�v�`�b�v�`��*/
	current_map_drawing(FLOOR, centerPos.x + dirX, centerPos.y + dirY, map);
	current_map_drawing(HOUSE, centerPos.x + dirX, centerPos.y + dirY, map);
	current_map_drawing(SHALLOW, centerPos.x + dirX, centerPos.y + dirY, map);
	current_map_drawing(WATER, centerPos.x + dirX, centerPos.y + dirY, map);
	current_map_drawing(WOODS, centerPos.x + dirX, centerPos.y + dirY, map);
}

/// <summary>
/// �X�V����
/// </summary>
void MapDraw::update() {

	/* 9�����̃}�b�v��`�� */
	drawing_current_maps(mapCentral, Central, Central); //�����}�b�v�i��ɕ\���j

	//y�����̃}�b�v�`�攻��
	if (blockArea.y <= TOP_BOUNDARY)
		drawing_current_maps(mapTopCentral, Central, Top); //��}�b�v
	else if (blockArea.y >= BOTTOM_BOUNDARY)
		drawing_current_maps(mapBottomCentral, Central, Bottom); //���}�b�v

	//x�����̃}�b�v�`�攻��
	if (blockArea.x <= LEFT_BOUNDARY)
		drawing_current_maps(mapLeftCentral, Left, Central); //���}�b�v
	else if (blockArea.x >= RIGHT_BOUNDARY)
		drawing_current_maps(mapRightCentral, Right, Central); //�E�}�b�v

	//�΂ߕ����̃}�b�v�`�攻��
	if (blockArea.x <= LEFT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		drawing_current_maps(mapTopLeft, Left, Top); //����}�b�v
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		drawing_current_maps(mapTopRight, Right, Top); //�E��}�b�v
	else if (blockArea.x <= LEFT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		drawing_current_maps(mapBottomLeft, Left, Bottom); //�����}�b�v
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		drawing_current_maps(mapBottomRight, Right, Bottom); //�E���}�b�v

	/* 8�����̏Փ˔��� */
	collisionDetection(LEFT, UP, LEFT_UP); //����
	collisionDetection(RIGHT, UP, RIGHT_UP); //�E��
	collisionDetection(LEFT, DOWN, LEFT_DOWN); //����
	collisionDetection(RIGHT, DOWN, RIGHT_DOWN); //�E��
	collisionDetection(LEFT, CENTER_Y, CENTER_LEFT); //������
	collisionDetection(RIGHT, CENTER_Y, CENTER_RIGHT); //�����E
	collisionDetection(CENTER_X, UP, CENTER_UP); //������
	collisionDetection(CENTER_X, DOWN, CENTER_DOWN); //������

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
/// �w�肵���ʒu�̏Փ˔���𓾂�
/// </summary>
/// <param name="x">x���̕���</param>
/// <param name="y">y���̕���</param>
/// <param name="direction">�������</param>
void MapDraw::collisionDetection(const int& x, const int& y, const int& direction) {
	collisionFlag[direction] = (mapCentral[currentCorner[y]][currentCorner[x]] == WOODS) ? true : false;
}
