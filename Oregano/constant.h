#pragma once

const int WIN_MAGNIFICATION = 100; //�E�C���h�E�{��
const int WIN_WIDTH = 16 * WIN_MAGNIFICATION; //�E�B���h�E����
const int WIN_HEIGHT = 9 * WIN_MAGNIFICATION; //�E�B���h�E�c��

const int BLOCK_SIZE = 64; //�u���b�N�T�C�Y
const int AREA_WIDTH = 25; //1�}�b�v�i���j�̉��̃T�C�Y
const int AREA_HEIGHT = 25; //1�}�b�v�i���j�̏c�̃T�C�Y
const int AREA_MIN = 0;
const int AREA_MAX = AREA_WIDTH - 1;

const int DIRECTION_SIZE = 4; //�����̎�ށi�z��̃T�C�Y�j

const int MOVING_DISTANCE = 8; //�ړ����x

const int INITIAL_X = 13600; //�����}�b�v��x���W
const int INITIAL_Y = 13200 + BLOCK_SIZE; //�����}�b�v��y���W

const int MOVE_RANGE = 10;

#define CALL_ONCE(src)\
     do {\
          static bool initialized = false;\
          if (!initialized){\
               src;\
               initialized = true;\
          }\
     } while (0)

//�Q�[���V�[��
enum GAME_SCENE {
	TITLE_SCENE,
	GAME_SCENE,
	MENU_SCENE,
	END_SCENE,
};

//�����̏��
enum DIRECTION_INFORMATION {
	LEFT,
	//���@
	RIGHT,
	//�E
	UP,
	//��
	DOWN,
	//��
	CENTER_X1,
	CENTER_X2,
	CENTER_Y1,
	CENTER_Y2,
	//����
	CROSS,
	//����
};

enum CORNER_INFORMATION {
	LEFT_UP,
	RIGHT_UP,
	LEFT_DOWN,
	RIGHT_DOWN,
	CENTER_LEFT1,
	CENTER_RIGHT1,
	CENTER_UP1,
	CENTER_DOWN1,
	CENTER_LEFT2,
	CENTER_RIGHT2,
	CENTER_UP2,
	CENTER_DOWN2,
};

enum DIRECTION_MAP {
	MAP_TOP_LEFT,
	MAP_TOP_CENTRAL,
	MAP_TOP_RIGHT,
	MAP_LEFT_CENTRAL,
	MAP_CENTRAL,
	MAP_RIGHT_CENTRAL,
	MAP_BOTTOM_LEFT,
	MAP_BOTTOM_CENTRAL,
	MAP_BOTTOM_RIGHT
};

enum DIRECTION_SIGN {
	Left = -1,
	Right = 1,
	Top = -1,
	Central = 0,
	Bottom = 1,
};

//�}�b�v�`�b�v����
enum MAP_INFORMATION {
	//��
	FLOOR,
	//�l
	BEACH,
	//����
	FLOWER = 8,
	//�L�m�R��
	MUSHROOM,
	//��
	HOUSE = 29,
	//��
	SHALLOW = 110,
	//��
	TIDE = 100,
	//����
	WATER = 120,
	//�N���X�^��
	CRYSTAL = 130,
	//��R
	STONE = 44,
	//�؁X
	WOODS = 40,
	//�z�Όn
	MINERAL = 49,
	//�c��
	BRIDGE_HEIGHT = 4,
	//����
	BRIDGE_WIDTH = 6,
	//��
	TREASURE_BOX = 300,
};

//�{�^�����
enum BUTTON {
	A,
	B,
	X,
	Y,
	LB,
	RB,
	VIEW,
	MENU,
	STICK_L,
	STICK_R
};

enum POSITION_INFORMATION {
	MAP_X,
	MAP_Y,
};

enum STATUS {
	LIFE,
	//������
	ATTACK,
	//�U����
	DEFENSE,
	//�����
	DEADLY_POISON_RESISTANCE,
	//�ғőϐ�
	DEADLY_POISON_VALUE,
	//�ғő����l
	PARALYSIS_RESISTANCE,
	//��ბϐ�
	PARALYSIS_VALUE,
	//��ბ����l
	HYPNOSIS_RESISTANCE,
	//�Ö��ϐ�
	HYPNOSIS_VALUE,
	//�Ö��ϐ�
	BLOODING_RESISTANCE,
	BLOODING_VALUE,
	PRIORITY,
	//�D��x
	CURRENT_MAP_X,
	CURRENT_MAP_Y,
	CENTRAL_POSITION_X,
	CENTRAL_POSITION_Y
};
