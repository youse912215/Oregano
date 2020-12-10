#pragma once
#include "constant_declaration.h"
#include "input.h"
#include <string>

using namespace std;

//--- �}�b�v�̊e�����̐錾 ---//
//extern int map_x;
//extern int map_y;

//extern int whole_map_position_x; //x�����ɂ����钆�S����̋���
//extern int whole_map_position_y; //y�����ɂ����钆�S����̋���

class Map_all : public Input {
private:
	string initial_csv; //�����n�_�̃}�b�v(����)
	const string comma = ","; //�J���}
	const string csv_num[16] = {
			"00", "01", "02", "03", "04", "05", "06", "07",
			"08", "09", "10", "11", "12", "13", "14", "15"
		}; //csv�t�@�C������ύX���邽�߂̐���
	string map_confirmation(const int& cx, const int& cy, string& csv);
public:
	static int map_x;
	static int map_y;
	int map_all[area_height][area_width];
	bool map_data[16][16];
	int current_map_x;
	int current_map_y;
	int map_width; //1�}�b�v������̔z��̉��T�C�Y
	int map_height; //1�}�b�v������̔z��̏c�T�C�Y]
	void get_map_data(const int& cx, const int& cy);
	void file_import(int map_xy[area_height][area_width]);
	void map_copy(int map_xy[area_height][area_width]);
	Map_all();
	~Map_all();
};
