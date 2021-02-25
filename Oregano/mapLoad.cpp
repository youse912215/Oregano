#include "mapLoad.h"
#include "constant.h"
#include "mapBase.h"

MapBase map;

MapLoad::MapLoad() :
	vecMap(AREA_HEIGHT, vector<int>(AREA_WIDTH)),
	mapAll(81, vector<vector<int>>(AREA_HEIGHT, vector<int>(AREA_WIDTH))) {
}

MapLoad::~MapLoad() {
}

/// <summary>
/// �}�b�v�f�[�^�z���ǂݍ��݁A�O�����z��Ɋi�[
/// </summary>
void MapLoad::roadMapData() {
	/*  */
	for (int y = 0; y < TOTAL_MAPS_Y; ++y) {
		for (int x = 0; x < TOTAL_MAPS_X; ++x) {
			map.fileImport(x, y, vecMap); //csv�t�@�C���ǂݍ���

			mapAll[x + y * TOTAL_MAPS_Y].clear(); //���g����U�N���A

			for (auto& i : vecMap) //�ǂݍ���2�����z��f�[�^��
				mapAll[x + y * TOTAL_MAPS_Y].push_back(i); //�����ɒl��}������
		}
	}
}
