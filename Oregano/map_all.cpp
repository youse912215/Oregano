#include "map_all.h"
#include "constant_declaration.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int Map_all::map_x = 6400; //x����
int Map_all::map_y = 6400; //y����

//������
Map_all::Map_all() : map_all(area_height, vector<int>(area_width)) {
	initial_csv = "resource/csv/map_x08y08.csv"; //�����n�_�̃}�b�v(����)
	map_width = map_all.at(0).size(); //���̃T�C�Y
	map_height = map_all.size(); //�c�̃T�C�Y
	current_map_x = map_x / (block_size * map_width); //���݂̑S�̃}�b�v��x���W
	current_map_y = map_y / (block_size * map_height); //���݂̑S�̃}�b�v��y���W
	sx = current_map_x - 8;
	sy = current_map_y - 8;
}

Map_all::~Map_all() {
}

/// <summary>
/// ���݂̍��W���m�F���A����ɉ�����csv�t�@�C����T��
/// </summary>
/// <param name="cx">���݂̑S�̃}�b�v��x���W</param>
/// <param name="cy">���݂̑S�̃}�b�v��y���W</param>
/// <param name="csv">csv�t�@�C����</param>
/// <returns>������ύX����csv�t�@�C������Ԃ�</returns>
string Map_all::map_confirmation(const int& cx, const int& cy, string& csv) {
	//if (csv == nullptr) { return; } //null�`�F�b�N
	csv.replace(18, 2, csv_num[cx]); //�t�@�C������x���W��ύX
	csv.replace(21, 2, csv_num[cy]); //�t�@�C������y���W��ύX
	return csv; //csv�t�@�C������Ԃ�
}

///// <summary>
///// �󂯎�����}�b�v�f�[�^���㏑������
///// </summary>
///// <param name="map_xy">�}�b�v���W[�c�T�C�Y][���T�C�Y]</param>
//void Map_all::map_copy(int map_xy[area_height][area_width]) {
//
//	for (int i = 0; i < area_width; i++) {
//		memcpy(map_xy[i], map_all[i], sizeof(int) * area_height);
//	}
//}

/// <summary>
/// �}�b�v�f�[�^�̃t�@�C���ǂݍ���
/// </summary>
void Map_all::file_import(const int& nx, const int& ny, vector<vector<int>>& map) {

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
