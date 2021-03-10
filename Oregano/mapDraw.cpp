#include "mapDraw.h"
#include "DxLib.h"

int MapDraw::mapX = INITIAL_X; //x����
int MapDraw::mapY = INITIAL_Y; //y����

MapDraw::MapDraw() : informationSize(15),

                     /* �e�p�̃}�b�v���W */
                     currentCorner(8),

                     /* 9�����̃}�b�v�z�� */
                     mapTopLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapTopCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapTopRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapLeftCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapRightCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapBottomLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapBottomCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                     mapBottomRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)) {
}

MapDraw::~MapDraw() {
}

void MapDraw::initialize() {
	/* ��ʏ�̍��W */
	screen.x = INITIAL_X - mapX;
	screen.y = INITIAL_Y - mapY;
	/* 1�}�b�v������̔z��T�C�Y */
	mapAspectSize.x = mapCentral.at(0).size();
	mapAspectSize.y = mapCentral.size();
	/* ���݂̃}�b�v���W */
	currentMap.x = mapX / (BLOCK_SIZE * mapAspectSize.x);
	currentMap.y = mapY / (BLOCK_SIZE * mapAspectSize.y);
	/* ���݂̃}�b�v�̋��E���W */
	currentBoundaryMap1.x = (mapX - HALF_BLOCK_SIZE) / (BLOCK_SIZE * mapAspectSize.x); //���[
	currentBoundaryMap1.y = (mapY - BLOCK_SIZE - QUARTER_BLOCK_SIZE) / (BLOCK_SIZE * mapAspectSize.y); //��[
	currentBoundaryMap2.x = (mapX + HALF_BLOCK_SIZE - 1) / (BLOCK_SIZE * mapAspectSize.x); //�E�[
	currentBoundaryMap2.y = (mapY + QUARTER_BLOCK_SIZE - 1) / (BLOCK_SIZE * mapAspectSize.y); //���[
	/* �}�b�v�̒����ʒu */
	centerPos.x = currentMap.x - (TOTAL_MAPS_X - 1);
	centerPos.y = currentMap.y - (TOTAL_MAPS_Y - 1);
	/* �}�b�v�ԋ����i1600px�j */
	mapBetweenDistance = BLOCK_SIZE * AREA_WIDTH;
	/* 1�u���b�N���i�}�b�v�j���̍��W */
	blockArea.x = (mapX / BLOCK_SIZE) % AREA_WIDTH;
	blockArea.y = (mapY / BLOCK_SIZE) % AREA_HEIGHT;

	currentCorner = {
			((mapX - 32) / BLOCK_SIZE) % AREA_WIDTH, ((mapX + 31) / BLOCK_SIZE) % AREA_WIDTH,
			((mapY - 48) / BLOCK_SIZE) % AREA_HEIGHT, ((mapY + 15) / BLOCK_SIZE) % AREA_HEIGHT,
			((mapX - 16) / BLOCK_SIZE) % AREA_WIDTH, ((mapX + 16) / BLOCK_SIZE) % AREA_WIDTH,
			((mapY - 32) / BLOCK_SIZE) % AREA_HEIGHT, (mapY / BLOCK_SIZE) % AREA_HEIGHT,
		};
}

/// <summary>
/// �ǂݍ��񂾃}�b�v�`�b�v�摜����}�b�v�`�悷��
/// </summary>
/// <param name="mapInformation"></param>
/// <param name="dirX">x�����̒��S����̋���</param>
/// <param name="dirY">y�����̒��S����̋���</param>
/// <param name="map">�}�b�v�̔z��</param>
void MapDraw::drawMapChips(const int& mapInformation, const int& dirX, const int& dirY,
                           vector<vector<int>>& map) {
	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < mapAspectSize.y; ++y) {
		for (int x = 0; x < mapAspectSize.x; ++x) {
			//mapInformation�̃`�b�v��Dest�̈ʒu�ɕ`��
			if (map[y][x] != mapInformation) continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
			DrawRectGraph(
				x * BLOCK_SIZE + screen.x + mapBetweenDistance * dirX,
				y * BLOCK_SIZE + screen.y + mapBetweenDistance * dirY,
				matrixX(mapInformation) * BLOCK_SIZE,
				matrixY(mapInformation) * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE,
				source_.mapChip, true, false);
		}
	}
}

/// <summary>
/// �}�b�v��񂩂�s�����o��
/// </summary>
/// <param name="mapInfo">�}�b�v�̏��</param>
int MapDraw::matrixX(const int& mapInfo) {
	return mapInfo % 10;
}

/// <summary>
/// �}�b�v��񂩂������o��
/// </summary>
/// <param name="mapInfo">�}�b�v�̏��</param>
int MapDraw::matrixY(const int& mapInfo) {
	return mapInfo / 10;
}

/// <summary>
/// ���S�����1�}�b�v������̋����ɂ���āA���݂̃}�b�v��`�悵�A�}�b�v�z���Ԃ�
/// </summary>
/// <param name="dirX">���S�����1�}�b�v������̋����ix�����j</param>
/// <param name="dirY">���S�����1�}�b�v������̋����iy�����j</param>
/// <param name="mapAll">�S�Ẵ}�b�v���i�[�����z��</param>
vector<vector<int>> MapDraw::drawCurrentMaps(const int& dirX, const int& dirY,
                                             vector<vector<vector<int>>>& mapAll) {
	/*�}�b�v�`�b�v�̕`��*/
	for (auto i = 0; i < informationSize; ++i) //�}�b�v���i���́j�̐������J��Ԃ�
		drawMapChips(i, centerPos.x + dirX, centerPos.y + dirY,
		             mapAll[(currentMap.x + dirX) + (currentMap.y + dirY) * TOTAL_MAPS_Y]);

	return mapAll[(currentMap.x + dirX) + (currentMap.y + dirY) * TOTAL_MAPS_Y]; //�����ɉ������}�b�v��Ԃ�
}

/// <summary>
/// �X�V����
/// </summary>
void MapDraw::update(vector<vector<vector<int>>>& mapAll) {
	initialize();

	/* 9�����̃}�b�v��`�� */
	mapCentral = drawCurrentMaps(Central, Central, mapAll); //�����}�b�v�i��ɕ\���j

	//y�����̃}�b�v�`�攻��
	if (blockArea.y <= TOP_BOUNDARY)
		mapTopCentral = drawCurrentMaps(Central, Top, mapAll); //��}�b�v
	else if (blockArea.y >= BOTTOM_BOUNDARY)
		mapBottomCentral = drawCurrentMaps(Central, Bottom, mapAll); //���}�b�v

	//x�����̃}�b�v�`�攻��
	if (blockArea.x <= LEFT_BOUNDARY)
		mapLeftCentral = drawCurrentMaps(Left, Central, mapAll); //���}�b�v
	else if (blockArea.x >= RIGHT_BOUNDARY)
		mapRightCentral = drawCurrentMaps(Right, Central, mapAll); //�E�}�b�v

	//�΂ߕ����̃}�b�v�`�攻��
	if (blockArea.x <= LEFT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		mapTopLeft = drawCurrentMaps(Left, Top, mapAll); //����}�b�v
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y <= TOP_BOUNDARY)
		mapTopRight = drawCurrentMaps(Right, Top, mapAll); //�E��}�b�v
	else if (blockArea.x <= LEFT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		mapBottomLeft = drawCurrentMaps(Left, Bottom, mapAll); //�����}�b�v
	else if (blockArea.x >= RIGHT_BOUNDARY && blockArea.y >= BOTTOM_BOUNDARY)
		mapBottomRight = drawCurrentMaps(Right, Bottom, mapAll); //�E���}�b�v
}
