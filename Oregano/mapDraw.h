#pragma once
#include "mapBase.h"
#include <vector>

using namespace std;

class MapDraw : public MapBase {
private:
	int graph; //�}�b�v�`�b�v�摜
	int column; //�s�ԍ�
	int row; //��ԍ�
	int blockAreaX; //1�u���b�N���i�}�b�v�j����x���W
	int blockAreaY; //1�u���b�N���i�}�b�v�j����y���W

	int currentMapX;
	int currentMapY;
	int mapWidth; //1�}�b�v������̔z��̉��T�C�Y
	int mapHeight; //1�}�b�v������̔z��̏c�T�C�Y]
	int initialX; //
	int initialY;

	vector<int> info; //�}�b�v�����

	vector<vector<int>> mapTopLeft; //����}�b�v
	vector<vector<int>> mapTopCentral; //��}�b�v
	vector<vector<int>> mapTopRight; //�E��}�b�v
	vector<vector<int>> mapLeftCentral; //���}�b�v
	vector<vector<int>> mapCentral; //�����}�b�v
	vector<vector<int>> mapRightCentral; //�E��}�b�v
	vector<vector<int>> mapBottomLeft; //�����}�b�v
	vector<vector<int>> mapBottomCentral; //���}�b�v
	vector<vector<int>> mapBottomRight; //�E���}�b�v

	vector<int> currentCorner; //���݂̊e�p�̃}�b�v���W�i�������܂ށj

	enum BOUNDARY {
		//�e���E
		LEFT_BOUNDARY = 12,
		RIGHT_BOUNDARY = 13,
		TOP_BOUNDARY = 7,
		BOTTOM_BOUNDARY = 17
	};

	void drawing_current_maps(vector<vector<int>>& map, const int& dirX, const int& dirY);
	void current_map_drawing(const int& map_info, const int& dirX, const int& dirY,
	                         vector<vector<int>>& map);
	void collisionDetection(const int& x, const int& y, const int& direction);

public:
	static int mapX; //�}�b�v���̒�����x���W
	static int mapY; //�}�b�v���̒�����y���W
	int screenX; //��ʏ��x���W
	int screenY; //��ʏ��y���W
	int mapBetweenDistance; //�}�b�v�ԋ����i800px�j
	vector<bool> collisionFlag; //�Փ˃t���O

	MapDraw(int graph);
	~MapDraw();
	void update();
};
