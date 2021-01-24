#pragma once

const int WINDOW_WIDTH = 1600; //�E�B���h�E����
const int WINDOW_HEIGHT = 900; //�E�B���h�E�c��
const int WIN_WIDTH = 800; //�E�B���h�E����
const int WIN_HEIGHT = 450; //�E�B���h�E�c��
const int block_size = 32; //�u���b�N�T�C�Y
const int area_width = 25; //1�}�b�v�i���j�̉��̃T�C�Y
const int area_height = 25; //1�}�b�v�i���j�̏c�̃T�C�Y
const int direction_size = 4; //�����̎�ށi�z��̃T�C�Y�j
const int moving_speed = 10; //�ړ����x
const int initial_map_x = 6800; //�����}�b�v��x���W
const int initial_map_y = 6625; //�����}�b�v��y���W

//�����̏��
enum direction {
	LEFT,
	//���@
	RIGHT,
	//�E
	UP,
	//��
	DOWN
	//��
};

enum dirction_sign {
	Left = -1,
	Right = 1,
	Top = -1,
	Central = 0,
	Bottom = 1,
};
