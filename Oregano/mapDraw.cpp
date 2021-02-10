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
	                              ((mapX - 16) / BLOCK_SIZE) % 25, ((mapY - 32) / BLOCK_SIZE) % 25,
	                              ((mapX + 16) / BLOCK_SIZE) % 25, (mapY / BLOCK_SIZE) % 25,
                              },

                              boundaryCriteria{
	                              currentCorner[LEFT] == AREA_MAX && currentCorner[RIGHT] == AREA_MIN
	                              && currentMap.x == currentBoundaryMap.x,
	                              currentCorner[LEFT] == AREA_MAX && currentCorner[RIGHT] == AREA_MIN
	                              && currentMap.x != currentBoundaryMap.x,
	                              currentCorner[UP] == AREA_MAX && currentCorner[DOWN] == AREA_MIN
	                              && currentMap.y == currentBoundaryMap.y,
	                              currentCorner[UP] == AREA_MAX && currentCorner[DOWN] == AREA_MIN
	                              && currentMap.y != currentBoundaryMap.y
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

                              collisionFlag(12) {
	/* �s��ԍ� */
	matrix.x = 0;
	matrix.y = 0;
	/* ��ʏ�̍��W */
	screen.x = INITIAL_X - mapX;
	screen.y = INITIAL_Y - mapY;
	/* 1�}�b�v������̔z��T�C�Y */
	mapAspectSize.x = mapBase.at(0).size();
	mapAspectSize.y = mapBase.size();
	/* ���݂̃}�b�v���W */
	currentMap.x = mapX / (BLOCK_SIZE * mapAspectSize.x);
	currentMap.y = mapY / (BLOCK_SIZE * mapAspectSize.y);
	/* ���݂̃}�b�v�̋��E���W */
	currentBoundaryMap.x = (mapX + 31) / (BLOCK_SIZE * mapAspectSize.x);
	currentBoundaryMap.y = (mapY + 15) / (BLOCK_SIZE * mapAspectSize.y);
	/* �}�b�v�̒����ʒu */
	centerPos.x = currentMap.x - 8;
	centerPos.y = currentMap.y - 8;
	/* �}�b�v�ԋ����i800px�j */
	mapBetweenDistance = BLOCK_SIZE * AREA_WIDTH;
	/* 1�u���b�N���i�}�b�v�j���̍��W */
	blockArea.x = (mapX / BLOCK_SIZE) % AREA_WIDTH;
	blockArea.y = (mapY / BLOCK_SIZE) % AREA_HEIGHT;
}

MapDraw::~MapDraw() {
}

/// <summary>
/// �ǂݍ��񂾃}�b�v�ɕ`�悷��
/// </summary>
/// <param name="mapInformation"></param>
/// <param name="dirX">x�����̒��S����̋���</param>
/// <param name="dirY">y�����̒��S����̋���</param>
/// <param name="map">�}�b�v�̔z��</param>
void MapDraw::current_map_drawing(const int& mapInformation, const int& dirX, const int& dirY,
                                  vector<vector<int>>& map) {

	mapName(&matrix.y, &matrix.x, mapInformation); //�}�b�v��񂩂��ƍs�����o��
	//�}�b�v�̕`��
	for (int y = 0; y < mapAspectSize.y; y++) {
		for (int x = 0; x < mapAspectSize.x; x++) {
			//mapInformation�̃`�b�v��Dest�̈ʒu�ɕ`��
			if (map[y][x] == mapInformation) {
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

	/* 12�����ŏՓ˔�����s�� */
	collisionDetection(LEFT, UP, LEFT_UP); //����
	collisionDetection(RIGHT, UP, RIGHT_UP); //�E��
	collisionDetection(LEFT, DOWN, LEFT_DOWN); //����
	collisionDetection(RIGHT, DOWN, RIGHT_DOWN); //�E��

	collisionDetection(LEFT, CENTER_Y1, CENTER_LEFT1); //������1
	collisionDetection(RIGHT, CENTER_Y1, CENTER_RIGHT1); //�����E1
	collisionDetection(CENTER_X1, UP, CENTER_UP1); //������1
	collisionDetection(CENTER_X1, DOWN, CENTER_DOWN1); //������1

	collisionDetection(LEFT, CENTER_Y2, CENTER_LEFT2); //������2
	collisionDetection(RIGHT, CENTER_Y2, CENTER_RIGHT2); //�����E2
	collisionDetection(CENTER_X2, UP, CENTER_UP2); //������2
	collisionDetection(CENTER_X2, DOWN, CENTER_DOWN2); //������2

	DrawFormatString(150, 0, GetColor(255, 255, 255), "LU:%d, RU:%d",
	                 mapCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(300, 0, GetColor(255, 255, 255), "LD:%d, RD:%d",
	                 mapCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);
	DrawFormatString(450, 0, GetColor(255, 255, 255), "CL:%d, CR:%d, CU:%d, CD:%d",
	                 mapCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]],
	                 mapCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]], false);
	DrawFormatString(150, 15, GetColor(255, 255, 255), "L:%d, R:%d",
	                 currentCorner[LEFT], currentCorner[RIGHT], false);
	DrawFormatString(300, 15, GetColor(255, 255, 255), "U:%d, D:%d",
	                 currentCorner[UP], currentCorner[DOWN], false);
	DrawFormatString(450, 15, GetColor(255, 255, 255), "CX:%d, CY:%d",
	                 currentCorner[CENTER_X1], currentCorner[CENTER_Y1], false);
	DrawFormatString(150, 30, GetColor(255, 255, 255),
	                 "(cy:%d, cx:%d)", currentCorner[CENTER_Y1], currentCorner[CENTER_X1], false);

	DrawFormatString(0, 15, GetColor(255, 255, 255), "(iniY:%d, iniX:%d)", centerPos.y, centerPos.x, false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d, %d", currentMap.y, currentMap.x, false);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "cby%d, cbx%d",
	                 currentBoundaryMap.y, currentBoundaryMap.x, false);
}

//--- 4�����i�㉺���E�j�̏Փ˔���̌��ʂ�Ԃ� ---//
bool MapDraw::leftCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_LEFT1])
		|| (collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_LEFT2]));
}

bool MapDraw::rightCollisionFlag() {
	return ((collisionFlag[RIGHT_UP] && collisionFlag[CENTER_RIGHT1])
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_RIGHT2]));
}

bool MapDraw::upCollisionFlag() {
	return ((collisionFlag[LEFT_UP] && collisionFlag[CENTER_UP1])
		|| (collisionFlag[RIGHT_UP] && collisionFlag[CENTER_UP2]));
}

bool MapDraw::downCollisionFlag() {
	return ((collisionFlag[LEFT_DOWN] && collisionFlag[CENTER_DOWN1])
		|| (collisionFlag[RIGHT_DOWN] && collisionFlag[CENTER_DOWN2]));
}

//----------------------------------------//

/// <summary>
/// �w�肵���ʒu�̏Փ˔���𓾂�
/// </summary>
/// <param name="x">x���̕���</param>
/// <param name="y">y���̕���</param>
/// <param name="direction">�������</param>
void MapDraw::collisionDetection(const int& x, const int& y, const int& direction) {

	/*�}�b�v���E���t�߂̂Ƃ��A�㉺���E�̃}�b�v�ō��W�𓾂�*/
	if (x == LEFT) {
		//������
		if (boundaryCriteria[x])
			collisionFlag[direction] = (mapLeftCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
		else
			collisionFlag[direction] = (mapCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
	}

	if (x == RIGHT) {
		//�E����
		if (boundaryCriteria[x])
			collisionFlag[direction] = (mapRightCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
		else
			collisionFlag[direction] = (mapCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
	}

	if (y == UP) {
		//�����
		if (boundaryCriteria[y])
			collisionFlag[direction] = (mapTopCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
		else
			collisionFlag[direction] = (mapCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
	}

	if (y == DOWN) {
		//������
		if (boundaryCriteria[y])
			collisionFlag[direction] = (mapBottomCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
		else
			collisionFlag[direction] = (mapCentral[currentCorner[y]][currentCorner[x]] != FLOOR) ? true : false;
	}
}
