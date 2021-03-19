#include "mapAutogeneration.h"
#include "random.h"
#include <algorithm>
#include <fstream>
#include <sstream>

MapAutoGeneration::MapAutoGeneration() :
	roadMap(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
	copyMap(TOTAL_MAPS_X * TOTAL_MAPS_Y, vector<vector<int>>(AREA_HEIGHT, vector<int>(AREA_WIDTH))) {
}

MapAutoGeneration::~MapAutoGeneration() {
}

/// <summary>
/// �}�b�v�̎�������
/// </summary>
/// <param name="random">�����_���֐��̒l</param>
/// <param name="randomMapNum">�����_���}�b�v���i�ԍ��j</param>
/// <returns></returns>
int MapAutoGeneration::autogenerationMap(const int& random, const int& randomMapNum) {
	/* �����_���}�b�v1 */
	if (randomMapNum == RANDOM_MAP1) {
		if (random < 25) return FLOOR_NORMAL;
		return WALL;
	}
	/* �����_���}�b�v2 */
	if (randomMapNum == RANDOM_MAP2) {
		if (random < 25) return FLOOR_NORMAL;
		if (random % 2 == 0) return POISON;
		return WALL;
	}
	return FLOOR_NORMAL; //�ȊO�̂Ƃ��ʏ폰��Ԃ�
}

/// <summary>
/// �����_���}�b�v�̐����������_���Ɋ��蓖��
/// </summary>
/// <param name="randomMapNum"></param>
void MapAutoGeneration::assigningRandomNum(const int& randomMapNum) {
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
void MapAutoGeneration::writeFile(const int& x, const int& y, vector<vector<int>>& map) {
	ofstream fileWrite(mapConfirmation(x, y, initialCsv));
	if (!fileWrite) return;

	for (unsigned int j = 0; j != map.at(0).size(); ++j) {
		for (unsigned int i = 0; i != map.size(); ++i) {
			fileWrite << map[j][i] << ","; //vector�z��̒������Ɋi�[
		}
		fileWrite << endl; //���s
	}

	fileWrite.close(); //����
}

/// <summary>
/// �����_���}�b�v�̃t�@�C����������
/// </summary>
void MapAutoGeneration::writeRandomMap() {

	for (unsigned int y = 0; y < TOTAL_MAPS_Y; ++y) {
		for (unsigned int x = 0; x < TOTAL_MAPS_X; ++x) {
			fileImport(x, y, roadMap); //�}�b�v�f�[�^�̃t�@�C���ǂݍ���

			saveInitMap(x, y); //�ŏ��̃}�b�v���R�s�[�i�ꎞ�ۑ��j

			assigningRandomNum(RANDOM_MAP1); //�����_���}�b�v1�̐����������_���Ɋ��蓖��
			assigningRandomNum(RANDOM_MAP2); //�����_���}�b�v2�̐����������_���Ɋ��蓖��

			writeFile(x, y, roadMap); //csv�t�@�C���̏�������
		}
	}
}

/// <summary>
/// �ŏ��̃}�b�v���R�s�[�i�ꎞ�ۑ��j
/// </summary>
/// <param name="x">�}�b�v��x���W</param>
/// <param name="y">�}�b�v��y���W</param>
void MapAutoGeneration::saveInitMap(const int& x, const int& y) {
	copyMap[x + y * TOTAL_MAPS_Y].clear(); //���g����U�N���A

	for (auto& i : roadMap) //�ǂݍ���2�����z��f�[�^��
		copyMap[x + y * TOTAL_MAPS_Y].push_back(i); //�����ɒl��}������
}

/// <summary>
/// CSV�t�@�C�����ŏ��̏�ԂɃ��Z�b�g
/// </summary>
void MapAutoGeneration::resetFile() {
	for (unsigned int y = 0; y < TOTAL_MAPS_Y; ++y) {
		for (unsigned int x = 0; x < TOTAL_MAPS_X; ++x) {
			writeFile(x, y, copyMap[x + y * TOTAL_MAPS_Y]);
		}
	}
}
