#pragma once
#include "mapBase.h"
#include "vec2.h"
#include <vector>

using namespace std;

class MapDraw : public MapBase {
private:
	int graph; //�}�b�v�摜
	int mapBetweenDistance; //�}�b�v�ԋ����i800px�j

	Vec2 matrix; //�s��ԍ�
	Vec2 screen; //��ʏ�̍��W
	Vec2 blockArea; //1�u���b�N���i�}�b�v�j���̍��W
	Vec2 currentMap; //���݂̃}�b�v���W
	Vec2 currentBoundaryMap1; //���݂̃}�b�v�̋��E���W
	Vec2 currentBoundaryMap2; //���݂̃}�b�v�̋��E���W
	Vec2 mapAspectSize; //1�}�b�v������̔z��̃T�C�Y
	Vec2 centerPos; //�}�b�v�̒����ʒu

	vector<int> information; //�}�b�v�����
	vector<int> currentCorner; //���݂̊e�p�̃}�b�v���W�i�������܂ށj
	vector<bool> boundaryCriteria; //�e�����̋��E����

	vector<vector<int>> mapTopLeft; //����}�b�v
	vector<vector<int>> mapTopCentral; //��}�b�v
	vector<vector<int>> mapTopRight; //�E��}�b�v
	vector<vector<int>> mapLeftCentral; //���}�b�v
	vector<vector<int>> mapCentral; //�����}�b�v
	vector<vector<int>> mapRightCentral; //�E��}�b�v
	vector<vector<int>> mapBottomLeft; //�����}�b�v
	vector<vector<int>> mapBottomCentral; //���}�b�v
	vector<vector<int>> mapBottomRight; //�E���}�b�v

	enum BOUNDARY {
		//�e���E
		LEFT_BOUNDARY = 12,
		RIGHT_BOUNDARY = 13,
		TOP_BOUNDARY = 7,
		BOTTOM_BOUNDARY = 17
	};

	void drawing_current_maps(vector<vector<int>>& map, const int& dirX, const int& dirY);
	void current_map_drawing(const int& mapInformation, const int& dirX, const int& dirY,
	                         vector<vector<int>>& map);
	void collisionDetection(const int& x, const int& y, const int& direction);
	void collisionDetectionLeftUp();
	void collisionDetectionRightUp();
	void collisionDetectionLeftDown();
	void collisionDetectionRightDown();
	void collisionDetectionCenterLeft1();
	void collisionDetectionCenterLeft2();
	void collisionDetectionCenterRight1();
	void collisionDetectionCenterRight2();
	void collisionDetectionCenterUp1();
	void collisionDetectionCenterUp2();
	void collisionDetectionCenterDown1();
	void collisionDetectionCenterDown2();

public:
	static int mapX; //�}�b�v���̒�����x���W
	static int mapY; //�}�b�v���̒�����y���W
	vector<bool> collisionFlag; //�Փ˃t���O

	MapDraw(int graph);
	~MapDraw();
	void update();
};
