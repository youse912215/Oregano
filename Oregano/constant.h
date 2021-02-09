#pragma once

const int WINDOW_WIDTH = 1600; //�E�B���h�E����
const int WINDOW_HEIGHT = 900; //�E�B���h�E�c��
const int WIN_MAGNIFICATION = 100;
const int WIN_WIDTH = 16 * WIN_MAGNIFICATION; //�E�B���h�E����
const int WIN_HEIGHT = 9 * WIN_MAGNIFICATION; //�E�B���h�E�c��
const int BLOCK_SIZE = 64; //�u���b�N�T�C�Y
const int AREA_WIDTH = 25; //1�}�b�v�i���j�̉��̃T�C�Y
const int AREA_HEIGHT = 25; //1�}�b�v�i���j�̏c�̃T�C�Y
const int DIRECTION_SIZE = 4; //�����̎�ށi�z��̃T�C�Y�j
const int MOVING_DISTANCE = 8; //�ړ����x
const int INITIAL_X = 13600; //�����}�b�v��x���W
const int INITIAL_Y = 13200 + BLOCK_SIZE; //�����}�b�v��y���W

//�����̏��
enum direction {
	LEFT,
	//���@
	RIGHT,
	//�E
	UP,
	//��
	DOWN,
	//��
	CENTER_X,
	CENTER_Y,
	//����
};

enum corner {
	LEFT_UP,
	RIGHT_UP,
	LEFT_DOWN,
	RIGHT_DOWN,
	CENTER_LEFT,
	CENTER_RIGHT,
	CENTER_UP,
	CENTER_DOWN
};

enum dirction_sign {
	Left = -1,
	Right = 1,
	Top = -1,
	Central = 0,
	Bottom = 1,
};

//--- �}�b�v�`�b�v���� ---//
enum map_info {
	//��
	FLOOR,
	//��
	HOUSE,
	//��
	SHALLOW,
	//��
	TIDE,
	//����
	WATER = 21,
	//��R
	STONE = 31,
	//�؁X
	WOODS = 41,
	//�c��
	BRIDGE_HEIGHT = 101,
	//����
	BRIDGE_WIDTH = 102
};
