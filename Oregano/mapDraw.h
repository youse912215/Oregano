#pragma once
#include "mapBase.h"
#include "dataSource.h"
#include "vec2.h"
#include <vector>

using namespace std;

class MapDraw : public MapBase {
private:
	DataSource source_;
	int mapBetweenDistance; //�}�b�v�ԋ����i1600px�j

	Vec2 screen; //��ʏ�̍��W

	Vec2 mapAspectSize; //1�}�b�v������̔z��̃T�C�Y
	Vec2 centerPos; //�}�b�v�̒����ʒu

	const int informationSize; //�}�b�v���

	/* �e�����̋��E */
	enum BOUNDARY {
		//��
		LEFT_BOUNDARY = 12,
		//�E
		RIGHT_BOUNDARY = 13,
		//��
		TOP_BOUNDARY = 7,
		//��
		BOTTOM_BOUNDARY = 17
	};

	//���S�����1�}�b�v������̋����ɂ���āA���݂̃}�b�v��`�悵�A�}�b�v�z���Ԃ�
	vector<vector<int>> drawCurrentMaps(const int& dirX, const int& dirY,
	                                    vector<vector<vector<int>>>& mapAll);
	//�ǂݍ��񂾃}�b�v�`�b�v��񂩂�}�b�v��`�悷��
	void drawMapChips(const int& mapInformation, const int& dirX, const int& dirY,
	                  vector<vector<int>>& map);

	int matrixX(const int& mapInfo); //�}�b�v��񂩂�s�����o��
	int matrixY(const int& mapInfo); //�}�b�v��񂩂������o��

public:
	static int mapX; //�}�b�v���̒�����x���W
	static int mapY; //�}�b�v���̒�����y���W

	Vec2 blockArea; //1�u���b�N���i�}�b�v�j���̍��W

	Vec2 currentMap; //���݂̃}�b�v���W
	Vec2 currentBoundaryMap1; //���݂̃}�b�v�̋��E���W
	Vec2 currentBoundaryMap2; //���݂̃}�b�v�̋��E���W

	vector<int> currentCorner; //���݂̊e�p�̃}�b�v���W�i�������܂ށj
	vector<vector<int>> mapTopLeft; //����}�b�v
	vector<vector<int>> mapTopCentral; //��}�b�v
	vector<vector<int>> mapTopRight; //�E��}�b�v
	vector<vector<int>> mapLeftCentral; //���}�b�v
	vector<vector<int>> mapCentral; //�����}�b�v
	vector<vector<int>> mapRightCentral; //�E��}�b�v
	vector<vector<int>> mapBottomLeft; //�����}�b�v
	vector<vector<int>> mapBottomCentral; //���}�b�v
	vector<vector<int>> mapBottomRight; //�E���}�b�v

	MapDraw();
	~MapDraw();

	void initialize(); //������

	void update(vector<vector<vector<int>>>& mapAll); //�X�V����
};
