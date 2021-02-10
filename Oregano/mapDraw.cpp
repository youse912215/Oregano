#include "mapDraw.h"
#include "coordinate_confirmation.h"
#include "mapInformation.h"
#include "DxLib.h"

int MapDraw::mapX = INITIAL_X; //x����
int MapDraw::mapY = INITIAL_Y; //y����

MapDraw::MapDraw(int graph) : graph(graph),
                              info{FLOOR, HOUSE, SHALLOW, TIDE, WATER, STONE, WOODS},
                              mapTopLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapTopCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapTopRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapLeftCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapRightCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomLeft(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomCentral(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              mapBottomRight(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
                              currentCorner{
	                              ((mapX - 32) / BLOCK_SIZE) % 25, ((mapX + 31) / BLOCK_SIZE) % 25,
	                              ((mapY - 48) / BLOCK_SIZE) % 25, ((mapY + 15) / BLOCK_SIZE) % 25,
	                              (mapX / BLOCK_SIZE) % 25, ((mapY - 16) / BLOCK_SIZE) % 25,
                              },
                              collisionFlag(8) {
	column = 0; //��
	row = 0; //�s
	screenX = INITIAL_X - mapX; //��ʏ��x���W
	screenY = INITIAL_Y - mapY; //��ʏ��y���W
	mapWidth = mapBase.at(0).size(); //���̃T�C�Y
	mapHeight = mapBase.size(); //�c�̃T�C�Y
	currentMapX = mapX / (BLOCK_SIZE * mapWidth); //���݂̑S�̃}�b�v��x���W
	currentMapY = mapY / (BLOCK_SIZE * mapHeight); //���݂̑S�̃}�b�v��y���W
	initialX = currentMapX - 8;
	initialY = currentMapY - 8;
	mapBetweenDistance = BLOCK_SIZE * AREA_WIDTH; //�}�b�v�ԋ����i800px�j
	blockAreaX = (mapX / BLOCK_SIZE) % AREA_WIDTH;
	blockAreaY = (mapY / BLOCK_SIZE) % AREA_HEIGHT;
}

MapDraw::~MapDraw() {
}


//---  ���݃}�b�v�Ə㉺���E�΂߂̍��v9�}�b�v��`��@---//

/// <summary>
/// �ǂݍ��񂾃}�b�v�ɕ`�悷��
/// </summary>
/// <param name="map_info"></param>
/// <param name="dirX">x�����̒��S����̋���</param>
/// <param name="dirY">y�����̒��S����̋���</param>
/// <param name="map">�}�b�v�̔z��</param>
void MapDraw::current_map_drawing(const int& map_info, const int& dirX, const int& dirY,
                                  vector<vector<int>>& map) {

	mapName(&column, &row, map_info); //�}�b�v��񂩂��ƍs�����o��
	//�}�b�v�̕`��
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			//map_info�̃`�b�v��dest�̈ʒu�ɕ`��
			if (map[y][x] == map_info) {
				DrawRectGraph(
					x * BLOCK_SIZE + screenX + mapBetweenDistance * dirX,
					y * BLOCK_SIZE + screenY + mapBetweenDistance * dirY,
					column * BLOCK_SIZE, row * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE,
					graph, true, false);
			}
		}
	}
}

/// <summary>
/// x,y��
/// </summary>
void MapDraw::drawing_current_maps(vector<vector<int>>& map, const int& dirX, const int& dirY) {
	fileImport(currentMapX + dirX, currentMapY + dirY, map); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(FLOOR, initialX + dirX, initialY + dirY, map);
	current_map_drawing(HOUSE, initialX + dirX, initialY + dirY, map);
	current_map_drawing(SHALLOW, initialX + dirX, initialY + dirY, map);
	current_map_drawing(WATER, initialX + dirX, initialY + dirY, map);
	current_map_drawing(WOODS, initialX + dirX, initialY + dirY, map);
	//---------------------//
}

/// <summary>
/// �X�V����
/// </summary>
void MapDraw::update() {

	/* 9�����̃}�b�v��`�� */
	drawing_current_maps(mapCentral, Central, Central); //�����}�b�v�i��ɕ\���j

	//y�����̃}�b�v�`�攻��
	if (blockAreaY <= TOP_BOUNDARY)
		drawing_current_maps(mapTopCentral, Central, Top); //��}�b�v
	else if (blockAreaY >= BOTTOM_BOUNDARY)
		drawing_current_maps(mapBottomCentral, Central, Bottom); //���}�b�v

	//x�����̃}�b�v�`�攻��
	if (blockAreaX <= LEFT_BOUNDARY)
		drawing_current_maps(mapLeftCentral, Left, Central); //���}�b�v
	else if (blockAreaX >= RIGHT_BOUNDARY)
		drawing_current_maps(mapRightCentral, Right, Central); //�E�}�b�v

	//�΂ߕ����̃}�b�v�`�攻��
	if (blockAreaX <= LEFT_BOUNDARY && blockAreaY <= TOP_BOUNDARY)
		drawing_current_maps(mapTopLeft, Left, Top); //����}�b�v
	else if (blockAreaX >= RIGHT_BOUNDARY && blockAreaY <= TOP_BOUNDARY)
		drawing_current_maps(mapTopRight, Right, Top); //�E��}�b�v
	else if (blockAreaX <= LEFT_BOUNDARY && blockAreaY >= BOTTOM_BOUNDARY)
		drawing_current_maps(mapBottomLeft, Left, Bottom); //�����}�b�v
	else if (blockAreaX >= RIGHT_BOUNDARY && blockAreaY >= BOTTOM_BOUNDARY)
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
	DrawFormatString(0, 15, GetColor(255, 255, 255), "(iniY:%d, iniX:%d)", initialY, initialX, false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d, %d", currentMapY, currentMapX, false);
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
