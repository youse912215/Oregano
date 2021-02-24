#include "mapDraw.h"
#include "DxLib.h"
#include "eventBase.h"

int MapDraw::mapX = INITIAL_X; //x����
int MapDraw::mapY = INITIAL_Y; //y����

MapDraw::MapDraw(int graph) : graph(graph),

                              information{
	                              FLOOR, BEACH, FLOWER, MUSHROOM, HOUSE, SHALLOW, TIDE, WATER,
	                              CRYSTAL, STONE,
	                              MINERAL, WOODS, BRIDGE_WIDTH, BRIDGE_HEIGHT, TREASURE_BOX
                              },

                              currentCorner{
	                              ((mapX - 32) / BLOCK_SIZE) % AREA_WIDTH, ((mapX + 31) / BLOCK_SIZE) % AREA_WIDTH,
	                              ((mapY - 48) / BLOCK_SIZE) % AREA_HEIGHT, ((mapY + 15) / BLOCK_SIZE) % AREA_HEIGHT,
	                              ((mapX - 16) / BLOCK_SIZE) % AREA_WIDTH, ((mapX + 16) / BLOCK_SIZE) % AREA_WIDTH,
	                              ((mapY - 32) / BLOCK_SIZE) % AREA_HEIGHT, (mapY / BLOCK_SIZE) % AREA_HEIGHT,
                              },


                              mapTopLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapTopCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapTopRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapLeftCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapRightCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)) {
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
/// �ǂݍ��񂾃}�b�v�`�b�v�摜����}�b�v�`��
/// </summary>
/// <param name="mapInformation"></param>
/// <param name="dirX">x�����̒��S����̋���</param>
/// <param name="dirY">y�����̒��S����̋���</param>
/// <param name="map">�}�b�v�̔z��</param>
void MapDraw::drawMapChips(const int& mapInformation, const int& dirX, const int& dirY,
                           vector<vector<int>>& map) {

	mapName(&matrix.y, &matrix.x, mapInformation); //�}�b�v��񂩂��ƍs�����o��
	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < mapAspectSize.y; ++y) {
		for (int x = 0; x < mapAspectSize.x; ++x) {
			//mapInformation�̃`�b�v��Dest�̈ʒu�ɕ`��
			if (map[y][x] != mapInformation) continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
			DrawRectGraph(
				x * BLOCK_SIZE + screen.x + mapBetweenDistance * dirX,
				y * BLOCK_SIZE + screen.y + mapBetweenDistance * dirY,
				matrix.y * BLOCK_SIZE, matrix.x * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE,
				graph, true, false);
		}
	}
}

/// <summary>
/// �}�b�v�̏������ƂɃ}�b�v�`�b�v�摜�̗�ƍs��Ԃ�
/// </summary>
/// <param name="column">��</param>
/// <param name="row">�s</param>
/// <param name="mapInfo">�}�b�v�̏��</param>
void MapDraw::mapName(int* column, int* row, const int& mapInfo) {
	if (column == nullptr || row == nullptr) { return; } //null�`�F�b�N

	*column = mapInfo % 10; //��̈ʂ���

	if (mapInfo != TIDE)
		*row = mapInfo / 10; //���}�b�v�ȊO�͏\�̈ʈȍ~����
	else
		*row = EventBase::night ? mapInfo / 10 : mapInfo / 10 - 1; //�����̒��}�b�v��󐣂ɕύX����
}

/// <summary>
/// �}�b�v�����ɂ�錻�݃}�b�v�̕`��
/// </summary>
void MapDraw::drawCurrentMaps(vector<vector<int>>& map, const int& dirX, const int& dirY) {
	fileImport(currentMap.x + dirX, currentMap.y + dirY, map); //csv�t�@�C���ǂݍ���
	/*�}�b�v�`�b�v�`��*/
	for (auto i : information)
		drawMapChips(i, centerPos.x + dirX, centerPos.y + dirY, map);
}

/// <summary>
/// �X�V����
/// </summary>
void MapDraw::update() {

	/* 9�����̃}�b�v��`�� */
	drawCurrentMaps(mapCentral, Central, Central); //�����}�b�v�i��ɕ\���j

	//y�����̃}�b�v�`�攻��
	if (blockArea.y <= TOP_BOUNDARY)
		drawCurrentMaps(mapTopCentral, Central, Top); //��}�b�v
	else if (blockArea.y >= BOTTOM_BOUNDARY)
		drawCurrentMaps(mapBottomCentral, Central, Bottom); //���}�b�v

	//x�����̃}�b�v�`�攻��
	if (blockArea.x <= LEFT_BOUNDARY)
		drawCurrentMaps(mapLeftCentral, Left, Central); //���}�b�v
	else if (blockArea.x >= RIGHT_BOUNDARY)
		drawCurrentMaps(mapRightCentral, Right, Central); //�E�}�b�v

	//�΂ߕ����̃}�b�v�`�攻��
	if (blockArea.x <= LEFT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		drawCurrentMaps(mapTopLeft, Left, Top); //����}�b�v
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		drawCurrentMaps(mapTopRight, Right, Top); //�E��}�b�v
	else if (blockArea.x <= LEFT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		drawCurrentMaps(mapBottomLeft, Left, Bottom); //�����}�b�v
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		drawCurrentMaps(mapBottomRight, Right, Bottom); //�E���}�b�v


	/*DrawFormatString(1000, 75, GetColor(255, 255, 255), "LU:%d, CU1:%d, CU2:%d, RU:%d",
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
	                 mapBottomCentral[currentCorner[DOWN]][currentCorner[RIGHT]], false);*/

	DrawFormatString(150, 15, GetColor(255, 255, 255), "L:%d, R:%d, U:%d, D:%d",
	                 currentCorner[LEFT], currentCorner[RIGHT], currentCorner[UP], currentCorner[DOWN], false);
	DrawFormatString(150, 30, GetColor(255, 255, 255), "CX1:%d, CX2:%d, CY1:%d, CY2:%d",
	                 currentCorner[CENTER_X1], currentCorner[CENTER_X2], currentCorner[CENTER_Y1],
	                 currentCorner[CENTER_Y2], false);

	DrawFormatString(0, 15, GetColor(255, 255, 255), "(iniY:%d, iniX:%d)", centerPos.y, centerPos.x, false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "mX%d, mY%d", currentMap.x, currentMap.y, false);
	DrawFormatString(0, 45, GetColor(255, 255, 255), "cby1:%d, cbx1:%d, cby2:%d, cbx2:%d",
	                 currentBoundaryMap1.y, currentBoundaryMap1.x, currentBoundaryMap2.y, currentBoundaryMap2.x, false);
	DrawFormatString(0, 880, GetColor(200, 120, 0), "X%d, Y%d", mapX, mapY, false);
}
