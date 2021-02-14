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
	                              ((mapX - 16) / BLOCK_SIZE) % 25, ((mapX + 16) / BLOCK_SIZE) % 25,
	                              ((mapY - 32) / BLOCK_SIZE) % 25, (mapY / BLOCK_SIZE) % 25,
                              },

                              boundaryCriteria{
	                              //������
	                              currentCorner[LEFT] == AREA_MAX && currentCorner[RIGHT] == AREA_MIN
	                              && currentMap.x >= currentBoundaryMap1.x && currentMap.x == currentBoundaryMap2.x,
	                              //�E����
	                              currentCorner[LEFT] == AREA_MAX && currentCorner[RIGHT] == AREA_MIN
	                              && currentMap.x == currentBoundaryMap1.x && currentMap.x <= currentBoundaryMap2.x,
	                              //�����
	                              currentCorner[UP] == AREA_MAX && currentCorner[DOWN] == AREA_MIN
	                              && currentMap.y >= currentBoundaryMap1.y && currentMap.y == currentBoundaryMap2.y,
	                              //������
	                              currentCorner[UP] == AREA_MAX && currentCorner[DOWN] == AREA_MIN
	                              && currentMap.y == currentBoundaryMap1.y && currentMap.y <= currentBoundaryMap2.y,
	                              //������1����
	                              currentCorner[CENTER_X1] == AREA_MAX && currentCorner[CENTER_X2] == AREA_MIN
	                              && currentMap.x >= currentBoundaryMap1.x && currentMap.x == currentBoundaryMap2.x,
	                              //������2����
	                              currentCorner[CENTER_X1] == AREA_MAX && currentCorner[CENTER_X2] == AREA_MIN
	                              && currentMap.x == currentBoundaryMap1.x && currentMap.x <= currentBoundaryMap2.x,
	                              //�����c1����
	                              currentCorner[CENTER_Y1] == AREA_MAX && currentCorner[CENTER_Y2] == AREA_MIN
	                              && currentMap.y >= currentBoundaryMap1.y && currentMap.y == currentBoundaryMap2.y,
	                              //�����c2����
	                              currentCorner[CENTER_Y1] == AREA_MAX && currentCorner[CENTER_Y2] == AREA_MIN
	                              && currentMap.y == currentBoundaryMap1.y && currentMap.y <= currentBoundaryMap2.y,
	                              //���E���������̓������
	                              currentCorner[LEFT] == AREA_MAX && currentCorner[RIGHT] == AREA_MIN
	                              && currentCorner[UP] == AREA_MAX && currentCorner[DOWN] == AREA_MIN
	                              && currentMap.x == currentBoundaryMap1.x && currentMap.y > currentBoundaryMap1.y
	                              && currentMap.x < currentBoundaryMap2.x && currentMap.y == currentBoundaryMap2.y
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
	currentBoundaryMap1.x = (mapX - 32) / (BLOCK_SIZE * mapAspectSize.x); //���[
	currentBoundaryMap1.y = (mapY - 48) / (BLOCK_SIZE * mapAspectSize.y); //��[
	currentBoundaryMap2.x = (mapX + 31) / (BLOCK_SIZE * mapAspectSize.x); //�E�[
	currentBoundaryMap2.y = (mapY + 15) / (BLOCK_SIZE * mapAspectSize.y); //���[
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
	collisionDetectionLeftUp(); //����
	collisionDetectionLeftDown(); //�E��
	collisionDetectionRightUp(); //����
	collisionDetectionRightDown(); //�E��

	collisionDetectionCenterLeft1(); //������1
	collisionDetectionCenterLeft2(); //������2
	collisionDetectionCenterRight1(); //�����E1
	collisionDetectionCenterRight2(); //�����E2

	collisionDetectionCenterUp1(); //������1
	collisionDetectionCenterUp2(); //������2
	collisionDetectionCenterDown1(); //������1
	collisionDetectionCenterDown2(); //������2

	DrawFormatString(1000, 75, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapCentral[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 90, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 105, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 120, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(700, 75, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapLeftCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapLeftCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapLeftCentral[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapLeftCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 90, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapLeftCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapLeftCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 105, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapLeftCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapLeftCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 120, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapLeftCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapLeftCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapLeftCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapLeftCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(1300, 75, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapRightCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapRightCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapRightCentral[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapRightCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 90, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapRightCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapRightCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 105, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapRightCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapRightCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 120, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapRightCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapRightCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapRightCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapRightCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(700, 0, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapTopLeft[currentCorner[UP]][currentCorner[LEFT]],
	                 mapTopLeft[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapTopLeft[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapTopLeft[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 15, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapTopLeft[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapTopLeft[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 30, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapTopLeft[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapTopLeft[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 45, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapTopLeft[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapTopLeft[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapTopLeft[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapTopLeft[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(1300, 0, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapTopRight[currentCorner[UP]][currentCorner[LEFT]],
	                 mapTopRight[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapTopRight[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapTopRight[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 15, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapTopRight[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapTopRight[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 30, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapTopRight[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapTopRight[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 45, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapTopRight[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapTopRight[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapTopRight[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapTopRight[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(1000, 0, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapTopCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapTopCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapTopCentral[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapTopCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 15, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapTopCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapTopCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 30, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapTopCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapTopCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 45, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapTopCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapTopCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapTopCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapTopCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(700, 150, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapBottomLeft[currentCorner[UP]][currentCorner[LEFT]],
	                 mapBottomLeft[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapBottomLeft[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapBottomLeft[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 165, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapBottomLeft[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapBottomLeft[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 180, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapBottomLeft[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapBottomLeft[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(700, 195, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapBottomLeft[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapBottomLeft[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapBottomLeft[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapBottomLeft[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(1300, 150, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapBottomRight[currentCorner[UP]][currentCorner[LEFT]],
	                 mapBottomRight[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapBottomRight[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapBottomRight[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 165, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapBottomRight[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapBottomRight[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 180, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapBottomRight[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapBottomRight[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1300, 195, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapBottomRight[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapBottomRight[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapBottomRight[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapBottomRight[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(1000, 150, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
	                 mapBottomCentral[currentCorner[UP]][currentCorner[LEFT]],
	                 mapBottomCentral[currentCorner[UP]][currentCorner[CENTER_X1]],
	                 mapBottomCentral[currentCorner[UP]][currentCorner[CENTER_X2]],
	                 mapBottomCentral[currentCorner[UP]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 165, GetColor(255, 255, 255), "CL1:%d,             CR1:%d",
	                 mapBottomCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]],
	                 mapBottomCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 180, GetColor(255, 255, 255), "CL2:%d,             CR2:%d",
	                 mapBottomCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]],
	                 mapBottomCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]], false);
	DrawFormatString(1000, 195, GetColor(255, 255, 255), "LD:%d, CD1:%d, CD2:%d, RD:%d",
	                 mapBottomCentral[currentCorner[DOWN]][currentCorner[LEFT]],
	                 mapBottomCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]],
	                 mapBottomCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]],
	                 mapBottomCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);

	DrawFormatString(150, 15, GetColor(255, 255, 255), "L:%d, R:%d, U:%d, D:%d",
	                 currentCorner[LEFT], currentCorner[RIGHT], currentCorner[UP], currentCorner[DOWN], false);
	DrawFormatString(150, 30, GetColor(255, 255, 255), "CX1:%d, CX2:%d, CY1:%d, CY2:%d",
	                 currentCorner[CENTER_X1], currentCorner[CENTER_X2], currentCorner[CENTER_Y1],
	                 currentCorner[CENTER_Y2], false);

	DrawFormatString(0, 15, GetColor(255, 255, 255), "(iniY:%d, iniX:%d)", centerPos.y, centerPos.x, false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d, %d", currentMap.y, currentMap.x, false);
	DrawFormatString(0, 45, GetColor(255, 255, 255), "cby1:%d, cbx1:%d, cby2:%d, cbx2:%d",
	                 currentBoundaryMap1.y, currentBoundaryMap1.x, currentBoundaryMap2.y, currentBoundaryMap2.x, false);
}


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

void MapDraw::collisionDetectionLeftUp() {
	if (boundaryCriteria[CROSS])
		collisionFlag[LEFT_UP] = (mapTopLeft[currentCorner[UP]][currentCorner[LEFT]] != FLOOR) ? true : false;
	else if (boundaryCriteria[LEFT])
		collisionFlag[LEFT_UP] = (mapLeftCentral[currentCorner[UP]][currentCorner[LEFT]] != FLOOR) ? true : false;
	else if (boundaryCriteria[UP])
		collisionFlag[LEFT_UP] = (mapTopCentral[currentCorner[UP]][currentCorner[LEFT]] != FLOOR) ? true : false;
	else
		collisionFlag[LEFT_UP] = (mapCentral[currentCorner[UP]][currentCorner[LEFT]] != FLOOR) ? true : false;
}

void MapDraw::collisionDetectionRightUp() {
	if (boundaryCriteria[CROSS] || boundaryCriteria[UP])
		collisionFlag[RIGHT_UP] = (mapTopCentral[currentCorner[UP]][currentCorner[RIGHT]] != FLOOR) ? true : false;
	else if (boundaryCriteria[RIGHT])
		collisionFlag[RIGHT_UP] = (mapRightCentral[currentCorner[UP]][currentCorner[RIGHT]] != FLOOR) ? true : false;

	else
		collisionFlag[RIGHT_UP] = (mapCentral[currentCorner[UP]][currentCorner[RIGHT]] != FLOOR) ? true : false;
}

void MapDraw::collisionDetectionLeftDown() {
	if (boundaryCriteria[LEFT] || boundaryCriteria[CROSS])
		collisionFlag[LEFT_DOWN] = (mapLeftCentral[currentCorner[DOWN]][currentCorner[LEFT]] != FLOOR) ? true : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[LEFT_DOWN] = (mapBottomCentral[currentCorner[DOWN]][currentCorner[LEFT]] != FLOOR) ? true : false;
	else
		collisionFlag[LEFT_DOWN] = (mapCentral[currentCorner[DOWN]][currentCorner[LEFT]] != FLOOR) ? true : false;
}

void MapDraw::collisionDetectionRightDown() {
	if (boundaryCriteria[RIGHT])
		collisionFlag[RIGHT_DOWN] = (mapRightCentral[currentCorner[DOWN]][currentCorner[RIGHT]] != FLOOR)
			                            ? true
			                            : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[RIGHT_DOWN] = (mapBottomCentral[currentCorner[DOWN]][currentCorner[RIGHT]] != FLOOR)
			                            ? true
			                            : false;
	else
		collisionFlag[RIGHT_DOWN] = (mapCentral[currentCorner[DOWN]][currentCorner[RIGHT]] != FLOOR) ? true : false;
}

void MapDraw::collisionDetectionCenterLeft1() {
	if (boundaryCriteria[CENTER_Y1])
		collisionFlag[CENTER_LEFT1] = (mapTopCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]] != FLOOR)
			                              ? true
			                              : false;
	else if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT1] = (mapLeftCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]] != FLOOR)
			                              ? true
			                              : false;
	else
		collisionFlag[CENTER_LEFT1] = (mapCentral[currentCorner[CENTER_Y1]][currentCorner[LEFT]] != FLOOR)
			                              ? true
			                              : false;
}

void MapDraw::collisionDetectionCenterLeft2() {
	if (boundaryCriteria[LEFT])
		collisionFlag[CENTER_LEFT2] = (mapLeftCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]] != FLOOR)
			                              ? true
			                              : false;
	else
		collisionFlag[CENTER_LEFT2] = (mapCentral[currentCorner[CENTER_Y2]][currentCorner[LEFT]] != FLOOR)
			                              ? true
			                              : false;
}

void MapDraw::collisionDetectionCenterRight1() {
	if (boundaryCriteria[CENTER_Y1])
		collisionFlag[CENTER_RIGHT1] = (mapTopCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]] != FLOOR)
			                               ? true
			                               : false;
	else if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT1] = (mapRightCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]] != FLOOR)
			                               ? true
			                               : false;
	else
		collisionFlag[CENTER_RIGHT1] = (mapCentral[currentCorner[CENTER_Y1]][currentCorner[RIGHT]] != FLOOR)
			                               ? true
			                               : false;
}

void MapDraw::collisionDetectionCenterRight2() {
	if (boundaryCriteria[RIGHT])
		collisionFlag[CENTER_RIGHT2] = (mapRightCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]] != FLOOR)
			                               ? true
			                               : false;
	else
		collisionFlag[CENTER_RIGHT2] = (mapCentral[currentCorner[CENTER_Y2]][currentCorner[RIGHT]] != FLOOR)
			                               ? true
			                               : false;
}

void MapDraw::collisionDetectionCenterUp1() {
	if (boundaryCriteria[CENTER_X1])
		collisionFlag[CENTER_UP1] = (mapLeftCentral[currentCorner[UP]][currentCorner[CENTER_X1]] != FLOOR)
			                            ? true
			                            : false;
	else if (boundaryCriteria[UP])
		collisionFlag[CENTER_UP1] = (mapTopCentral[currentCorner[UP]][currentCorner[CENTER_X1]] != FLOOR)
			                            ? true
			                            : false;
	else
		collisionFlag[CENTER_UP1] = (mapCentral[currentCorner[UP]][currentCorner[CENTER_X1]] != FLOOR)
			                            ? true
			                            : false;
}

void MapDraw::collisionDetectionCenterUp2() {
	if (boundaryCriteria[CENTER_X2])
		collisionFlag[CENTER_UP2] = (mapRightCentral[currentCorner[UP]][currentCorner[CENTER_X2]] != FLOOR)
			                            ? true
			                            : false;
	else if (boundaryCriteria[UP])
		collisionFlag[CENTER_UP2] = (mapTopCentral[currentCorner[UP]][currentCorner[CENTER_X2]] != FLOOR)
			                            ? true
			                            : false;
	else
		collisionFlag[CENTER_UP2] = (mapCentral[currentCorner[UP]][currentCorner[CENTER_X2]] != FLOOR)
			                            ? true
			                            : false;
}

void MapDraw::collisionDetectionCenterDown1() {
	if (boundaryCriteria[CENTER_X1])
		collisionFlag[CENTER_DOWN1] = (mapLeftCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]] != FLOOR)
			                              ? true
			                              : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[CENTER_DOWN1] = (mapBottomCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]] != FLOOR)
			                              ? true
			                              : false;
	else
		collisionFlag[CENTER_DOWN1] = (mapCentral[currentCorner[DOWN]][currentCorner[CENTER_X1]] != FLOOR)
			                              ? true
			                              : false;
}

void MapDraw::collisionDetectionCenterDown2() {
	if (boundaryCriteria[CENTER_X2])
		collisionFlag[CENTER_DOWN2] = (mapRightCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]] != FLOOR)
			                              ? true
			                              : false;
	else if (boundaryCriteria[DOWN])
		collisionFlag[CENTER_DOWN2] = (mapBottomCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]] != FLOOR)
			                              ? true
			                              : false;
	else
		collisionFlag[CENTER_DOWN2] = (mapCentral[currentCorner[DOWN]][currentCorner[CENTER_X2]] != FLOOR)
			                              ? true
			                              : false;
}
