#pragma once
#include "constant.h"
#include "inputProcess.h"
#include <string>
#include <vector>

using namespace std;

class MapBase : public Input {
private:
	string initial_csv; //�����n�_�̃}�b�v(����)
	const string comma = ","; //�J���}
	const string csv_num[16] = {
			"00", "01", "02", "03", "04", "05", "06", "07",
			"08", "09", "10", "11", "12", "13", "14", "15"
		}; //csv�t�@�C������ύX���邽�߂̐���
	string map_confirmation(const int& cx, const int& cy, string& csv);

protected:
	vector<vector<int>> map_all;
	void file_import(const int& nx, const int& ny, vector<vector<int>>& map);
	//void map_copy(int map_xy[AREA_HEIGHT][AREA_WIDTH]);
	MapBase();
	~MapBase();

public:

};
