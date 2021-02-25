#pragma once
#include "constant.h"
#include <string>
#include <vector>

using namespace std;

class MapBase {
private:
	const string comma = ","; //�J���}
	const string csvNum[9] = {
			"00", "01", "02", "03", "04", "05", "06", "07", "08",
		}; //csv�t�@�C������ύX���邽�߂̐���


protected:
	vector<vector<int>> mapBase; //�x�[�X�ƂȂ�}�b�v

	string initialCsv; //�����n�_�̃}�b�v(����)
	string mapConfirmation(const int& cx, const int& cy, string& csv);

	void fileImport(const int& nx, const int& ny, vector<vector<int>>& map);

public:
	MapBase();
	~MapBase();


};
