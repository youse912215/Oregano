#include "mapBase.h"
#include "constant.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//������
MapBase::MapBase() : map_all(AREA_HEIGHT, vector<int>(AREA_WIDTH)) {
	initial_csv = "resource/csv/map_x08y08.csv"; //�����n�_�̃}�b�v(����)
}

MapBase::~MapBase() {
}

/// <summary>
/// ���݂̍��W���m�F���A����ɉ�����csv�t�@�C����T��
/// </summary>
/// <param name="cx">���݂̑S�̃}�b�v��x���W</param>
/// <param name="cy">���݂̑S�̃}�b�v��y���W</param>
/// <param name="csv">csv�t�@�C����</param>
/// <returns>������ύX����csv�t�@�C������Ԃ�</returns>
string MapBase::map_confirmation(const int& cx, const int& cy, string& csv) {
	//if (csv == nullptr) { return; } //null�`�F�b�N
	csv.replace(18, 2, csv_num[cx]); //�t�@�C������x���W��ύX
	csv.replace(21, 2, csv_num[cy]); //�t�@�C������y���W��ύX
	return csv; //csv�t�@�C������Ԃ�
}

///// <summary>
///// �󂯎�����}�b�v�f�[�^���㏑������
///// </summary>
///// <param name="map_xy">�}�b�v���W[�c�T�C�Y][���T�C�Y]</param>
//void MapBase::map_copy(int map_xy[AREA_HEIGHT][AREA_WIDTH]) {
//
//	for (int i = 0; i < AREA_WIDTH; i++) {
//		memcpy(map_xy[i], map_all[i], sizeof(int) * AREA_HEIGHT);
//	}
//}

/// <summary>
/// �}�b�v�f�[�^�̃t�@�C���ǂݍ���
/// </summary>
void MapBase::file_import(const int& nx, const int& ny, vector<vector<int>>& map) {

	ifstream file(map_confirmation(nx, ny, initial_csv));
	string line;
	int j = 0;
	while (getline(file, line)) {
		int i = 0;
		// �J���}����؂蕶���Ƃ��Đ؂蕪���Aint�ɕϊ�����data[][]�Ɋi�[����
		for (string::size_type spos, epos = 0;
		     (spos = line.find_first_not_of(comma, epos)) != string::npos;) {
			string token = line.substr(spos, (epos = line.find_first_of(comma, spos)) - spos);
			map[j][i++] = stoi(token);
		}
		++j;
	}
}
