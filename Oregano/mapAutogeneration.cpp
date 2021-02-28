#include "mapAutogeneration.h"
#include "random.h"
#include "DxLib.h"
#include <algorithm>
#include <fstream>
#include <sstream>

MapAutogeneration::MapAutogeneration() : roadMap(AREA_HEIGHT, vector<int>(AREA_WIDTH)) {
}

MapAutogeneration::~MapAutogeneration() {
}

/// <summary>
/// �}�b�v�̎�������
/// </summary>
/// <param name="random">�����_���֐��̒l</param>
/// <param name="randomMapNum">�����_���}�b�v���i�ԍ��j</param>
/// <returns></returns>
int MapAutogeneration::autogenerationMap(const int& random, const int& randomMapNum) {
	/* �����_���}�b�v1 */
	if (randomMapNum == RANDOM_MAP1) {
		if (random < 25) return FLOOR;
		if (random % 2 == 0) return WOODS;
		if (random == 25) return MUSHROOM;
		if (random == 27) return SHALLOW;
		return FLOWER;
	}
	/* �����_���}�b�v2 */
	if (randomMapNum == RANDOM_MAP2) {
		if (random < 25) return FLOOR;
		if (random % 2 == 0) return WITHERED_WOODS;
		if (random == 25) return POISON;
		if (random == 27) return MUSHROOM;
		return FLOWER;
	}
	return FLOOR; //�ȊO�̂Ƃ��ʏ폰��Ԃ�
}

/// <summary>
/// �����_���}�b�v�̐����������_���Ɋ��蓖��
/// </summary>
/// <param name="randomMapNum"></param>
void MapAutogeneration::AssigningRandomNum(const int& randomMapNum) {
	vector<int>::iterator itr;
	int index = 0;
	bool loop = false;
	while (!loop) {
		for (unsigned int i = 0; i != roadMap.size();) {

			itr = find(roadMap[i].begin(), roadMap[i].end(), randomMapNum); //�Ώۂ̃C�e���[�^�[��������

			if (itr != roadMap[i].end()) {
				index = distance(roadMap[i].begin(), itr); //�����_���}�b�v�̃C���f�b�N�X�����
				roadMap[i][index] = autogenerationMap(getRandom(0, 30), randomMapNum); //�}�b�v�̎�������
			}
			else {
				++i; //���Z
			}
		}
		loop = true; //while�𔲂���
	}
}

/// <summary>
/// csv�t�@�C���̏�������
/// </summary>
/// <param name="x">�}�b�v��x���W</param>
/// <param name="y">�}�b�v��y���W</param>
void MapAutogeneration::fileWrite(const int& x, const int& y) {
	ofstream fileWrite(mapConfirmation(x, y, initialCsv));
	if (!fileWrite) return;

	for (unsigned int j = 0; j != roadMap.at(0).size(); ++j) {
		for (unsigned int i = 0; i != roadMap.size(); ++i) {
			fileWrite << roadMap[j][i] << ","; //vector�z��̒������Ɋi�[
		}
		fileWrite << endl; //���s
	}

	fileWrite.close(); //����
}

/// <summary>
/// �����_���}�b�v�̃t�@�C����������
/// </summary>
void MapAutogeneration::writeRandomMap() {

	for (unsigned int y = 5; y < 9; ++y) {
		for (unsigned int x = 4; x < 9; ++x) {
			fileImport(x, y, roadMap); //�}�b�v�f�[�^�̃t�@�C���ǂݍ���

			AssigningRandomNum(RANDOM_MAP1); //�����_���}�b�v1�̐����������_���Ɋ��蓖��
			AssigningRandomNum(RANDOM_MAP2); //�����_���}�b�v2�̐����������_���Ɋ��蓖��

			fileWrite(x, y); //csv�t�@�C���̏�������
		}
	}
}
