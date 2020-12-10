#include "map_draw.h"
#include "coordinate_confirmation.h"
#include "map_info.h"

void Map_draw::drawing_top_left() {
	file_import(map_top_left); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, -1, -1, map_top_left);
	current_map_drawing(house, -1, -1, map_top_left);
	current_map_drawing(shallow, -1, -1, map_top_left);
	current_map_drawing(water, -1, -1, map_top_left);
	current_map_drawing(woods, -1, -1, map_top_left);
	//---------------------//
	//map_copy(map_top_left); //csv�t�@�C��
}

void Map_draw::drawing_top_central() {
	file_import(map_top_central); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, 0, -1, map_top_central);
	current_map_drawing(house, 0, -1, map_top_central);
	current_map_drawing(shallow, 0, -1, map_top_central);
	current_map_drawing(water, 0, -1, map_top_central);
	current_map_drawing(woods, 0, -1, map_top_central);
	//---------------------//
	//map_copy(map_top_central); //csv�t�@�C��
}

void Map_draw::drawing_top_right() {
	file_import(map_top_right); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, 1, -1, map_top_right);
	current_map_drawing(house, 1, -1, map_top_right);
	current_map_drawing(shallow, 1, -1, map_top_right);
	current_map_drawing(water, 1, -1, map_top_right);
	current_map_drawing(woods, 1, -1, map_top_right);
	//---------------------//
	//map_copy(map_top_right); //csv�t�@�C��
}

void Map_draw::drawing_left_central() {
	file_import(map_left_central); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, -1, 0, map_left_central);
	current_map_drawing(house, -1, 0, map_left_central);
	current_map_drawing(shallow, -1, 0, map_left_central);
	current_map_drawing(water, -1, 0, map_left_central);
	current_map_drawing(woods, -1, 0, map_left_central);
	//---------------------//
	//map_copy(map_left_central); //csv�t�@�C��
}

void Map_draw::drawing_central() {
	file_import(map_central); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, 0, 0, map_central);
	current_map_drawing(house, 0, 0, map_central);
	current_map_drawing(shallow, 0, 0, map_central);
	current_map_drawing(water, 0, 0, map_central);
	current_map_drawing(woods, 0, 0, map_central);
	//---------------------//
	//map_copy(map_central); //csv�t�@�C��
}

void Map_draw::drawing_right_central() {
	file_import(map_right_central); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, 1, 0, map_right_central);
	current_map_drawing(house, 1, 0, map_right_central);
	current_map_drawing(shallow, 1, 0, map_right_central);
	current_map_drawing(water, 1, 0, map_right_central);
	current_map_drawing(woods, 1, 0, map_right_central);
	//---------------------//
	//map_copy(map_right_central); //csv�t�@�C��
}

void Map_draw::drawing_bottom_left() {
	file_import(map_bottom_left); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, -1, 1, map_bottom_left);
	current_map_drawing(house, -1, 1, map_bottom_left);
	current_map_drawing(shallow, -1, 1, map_bottom_left);
	current_map_drawing(water, -1, 1, map_bottom_left);
	current_map_drawing(woods, -1, 1, map_bottom_left);
	//---------------------//
	//map_copy(map_bottom_left); //csv�t�@�C��
}

void Map_draw::drawing_bottom_central() {
	file_import(map_bottom_central); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, 0, 1, map_bottom_central);
	current_map_drawing(house, 0, 1, map_bottom_central);
	current_map_drawing(shallow, 0, 1, map_bottom_central);
	current_map_drawing(water, 0, 1, map_bottom_central);
	current_map_drawing(woods, 0, 1, map_bottom_central);
	//---------------------//
	//map_copy(map_bottom_central); //csv�t�@�C��
}

void Map_draw::drawing_bottom_right() {
	file_import(map_bottom_right); //csv�t�@�C���ǂݍ���
	//--- �}�b�v�`�b�v�`�� ---//
	current_map_drawing(_floor, 1, 1, map_bottom_right);
	current_map_drawing(house, 1, 1, map_bottom_right);
	current_map_drawing(shallow, 1, 1, map_bottom_right);
	current_map_drawing(water, 1, 1, map_bottom_right);
	current_map_drawing(woods, 1, 1, map_bottom_right);
	//---------------------//
	//map_copy(map_bottom_right); //csv�t�@�C��
}

/// <summary>
/// 9�}�b�v�̕`��
/// </summary>
void Map_draw::drawing_map() {
	drawing_top_left();
	drawing_top_central();
	drawing_top_right();
	drawing_left_central();
	drawing_central();
	drawing_right_central();
	drawing_bottom_left();
	drawing_bottom_central();
	drawing_bottom_right();
};
