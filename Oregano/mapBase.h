#pragma once
#include "constant.h"
#include "inputProcess.h"
#include <string>
#include <vector>

using namespace std;

class MapBase : public Input {
private:
	string initialCsv; //�����n�_�̃}�b�v(����)
	const string comma = ","; //�J���}
	const string csvNum[16] = {
			"00", "01", "02", "03", "04", "05", "06", "07",
			"08", "09", "10", "11", "12", "13", "14", "15"
		}; //csv�t�@�C������ύX���邽�߂̐���
	string mapConfirmation(const int& cx, const int& cy, string& csv);

protected:
	vector<vector<int>> mapBase; //�x�[�X�ƂȂ�}�b�v

	void fileImport(const int& nx, const int& ny, vector<vector<int>>& map);
	MapBase();
	~MapBase();

public:

};
