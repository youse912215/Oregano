#pragma once
#include "constant.h"
#include <string>
#include <vector>

using namespace std;

class MapBase {
private:
	const string comma = ","; //�J���}
	const string csvNum[TOTAL_MAPS_X] = {
			"00", "01", "02", "03", "04", "05", "06", "07", "08",
		}; //csv�t�@�C������ύX���邽�߂̐���


protected:
	string initialCsv; //�����n�_�̃}�b�v(����)
	string mapConfirmation(const int& cx, const int& cy, string& csv); //���݂̃}�b�v���W�ɂ���āAcsv�t�@�C����ύX

public:
	MapBase();
	~MapBase();

	void fileImport(const int& nx, const int& ny, vector<vector<int>>& map); //�}�b�v�f�[�^�̓ǂݍ���
};
