#pragma once

const int WIN_MAGNIFICATION = 100; //�E�C���h�E�{��
const int WIN_WIDTH = 16 * WIN_MAGNIFICATION; //�E�B���h�E����
const int WIN_HEIGHT = 9 * WIN_MAGNIFICATION; //�E�B���h�E�c��

const int BLOCK_SIZE = 64; //�u���b�N�T�C�Y�iint�^�j
const int HALF_BLOCK_SIZE = 32; //�u���b�N�T�C�Y��1/2�iint�^�j
const int QUARTER_BLOCK_SIZE = 16; //�u���b�N�T�C�Y��1/2�iint�^�j

const int AREA_WIDTH = 25; //1�}�b�v���̉��̃T�C�Y
const int AREA_HEIGHT = 25; //1�}�b�v���̏c�̃T�C�Y
const int AREA_MIN = 0; //���̍ŏ��l
const int AREA_MAX = AREA_WIDTH - 1; //���̍ő�l

const double HALF_BLOCK_SIZE_D = 32.0; //�u���b�N�T�C�Y��1/2�idouble�^�j
const double QUARTER_BLOCK_SIZE_D = HALF_BLOCK_SIZE_D / 2.0; //�u���b�N�T�C�Y��1/4�idouble�^�j

const double ENEMY_COLLISION_DISTANCE = 48.0; //�G�Ƃ̏Փˋ���
const double WEAPON_COLLISION_DISTANCE = HALF_BLOCK_SIZE_D; //�G�ƕ���Ƃ̏Փˋ���

const int TOTAL_MAPS_X = 5; //�������̃}�b�v����
const int TOTAL_MAPS_Y = 5; //�c�����̃}�b�v����

const int ONE_MAP_X = BLOCK_SIZE * AREA_WIDTH;
const int ONE_MAP_Y = BLOCK_SIZE * AREA_HEIGHT;

const int HALF_MAP_X = ONE_MAP_X / 2; //1�}�b�v�̔����T�C�Y
const int HALF_MAP_Y = ONE_MAP_Y / 2; //1�}�b�v�̔����T�C�Y

const int KEY_BUFFER_MAX = 256; //�L�[�̃o�b�t�@�̍ő�

const int DIRECTION_SIZE = 4; //�����̎�ށi�z��̃T�C�Y�j

const int MOVING_DISTANCE = 8; //�ړ�����
const double KNIFE_SPEED = 16.0; //�i�C�t���x

const int INITIAL_X = ONE_MAP_X * (TOTAL_MAPS_X - 1) + HALF_MAP_X; //�����}�b�v��x���W
const int INITIAL_Y = ONE_MAP_Y * (TOTAL_MAPS_Y - 1) + HALF_MAP_Y / 2 + BLOCK_SIZE; //�����}�b�v��y���W

const int MOVE_RANGE = 1000; //�ړ��͈́i���̐����̃}�b�v�`�b�v�܂ňړ��\�j

const int GAME_HOUR = 1200; //1���Ԃ������gameTime

const int PLAYER_STATUS_SIZE = 21; //�v���C���[�X�e�[�^�X(�����ȊO)�̃T�C�Y
const int PLAYER_ITEM_SIZE = 160; //�v���C���[�̃A�C�e���T�C�Y
const int PLAYER_ACCESSORY_SIZE = 80; //�v���C���[�̃A�N�Z�T���[�T�C�Y
const int PLAYER_JEWEL_SIZE = 32; //�v���C���[�̃W���G���T�C�Y
const int PLAYER_MINERAL_SIZE = 8; //�v���C���[�̍z���T�C�Y

const int STATUS_INFORMATION_SIZE = PLAYER_STATUS_SIZE + 2; //�X�e�[�^�X�̃T�C�Y
const int COIN_INFORMATION_SIZE = 4312; //�R�C�����̃T�C�Y
const int ITEM_INFORMATION_SIZE = 2120; //�A�C�e�����̃T�C�Y
const int ACCESSORY_INFORMATION_SIZE = 128; //�A�N�Z�T���[���̃T�C�Y
const int JEWEL_INFORMATION_SIZE = 72; //�W���G�����̃T�C�Y
const int MINERAL_INFORMATION_SIZE = 128; //�z�����̃T�C�Y 
const int EVENT_INFORMATION_SIZE = 8; //1�C�x���g������̏��̃T�C�Y

const int COIN_EVENT_SIZE = 250; //�R�C���C�x���g�̃T�C�Y
const int ITEM_EVENT_SIZE = 120; //�A�C�e���C�x���g�̃T�C�Y
const int ACCESSORY_EVENT_SIZE = 20; //�A�N�Z�T���[�C�x���g�̃T�C�Y
const int JEWEL_EVENT_SIZE = 5; //�W���G���C�x���g�̃T�C�Y
const int MINERAL_EVENT_SIZE = 20; //�z���C�x���g�̃T�C�Y

const int ALL_COIN_TYPE = 4; //�R�C���̎��

const int TERMINAL_CHAR = 1;

//��x�̂݌Ăяo��
#define CALL_ONCE(/*src*/function)\
     do {\
          static bool initialized = false;\
          if (!initialized){\
               /*src*/function;\
               initialized = true;\
          }\
     } while (0)

//�Q�[���V�[��
enum GAME_SCENE {
	TITLE_SCENE,
	ROAD_SCENE,
	GAME_SCENE,
	MENU_ITEM_SCENE,
	MENU_STATUS_SCENE,
	MENU_EQUIPMENT_SCENE,
	END_SCENE,
};

//�����̏��
enum DIRECTION_INFORMATION {
	//��
	LEFT,
	//�E
	RIGHT,
	//��
	UP,
	//��
	DOWN,
	//������
	CENTER_X1,
	//�����E
	CENTER_X2,
	//������
	CENTER_Y1,
	//������
	CENTER_Y2,
	//����
	CROSS,
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
	//�ԏ�
	FLOOR_FLOWER,
	//�󔠂̏�
	FLOOR_TREASURE,
	//���i�ʏ퓹�j
	FLOOR_NORMAL,
	//��1
	FLOWER1,
	//��2
	FLOWER2,
	//�ł��ڂ�
	ROUGH,
	//��
	SHALLOW,
	//����
	SWAMP,
	//�ŏ�
	POISON,
	//�X��
	ICE,
	//�����_���}�b�v(�X)
	RANDOM_MAP1,
	//�����_���}�b�v2(���n)
	RANDOM_MAP2,
	//��
	WALL,
	//�O�C
	SEA,
	//��
	TREASURE_BOX,
};

//�{�^�����
enum BUTTON {
	A_BUTTON,
	B_BUTTON,
	X_BUTTON,
	Y_BUTTON,
	L_BUTTON,
	R_BUTTON,
	VIEW_BUTTON,
	MENU_BUTTON,
	STICK_L_BUTTON,
	STICK_R_BUTTON,
	STICK_LEFT,
	STICK_RIGHT,
	STICK_UP,
	STICK_DOWN
};

enum POSITION_INFORMATION {
	POSITION_X,
	POSITION_Y,
};

enum STATUS {
	//�g���W���[�����N
	TREASURE_RANK,
	//�ԖG�K�̃R�C��
	GREEN_COIN,
	//�������̃R�C��
	YELLOW_COIN,
	//�������̃R�C��
	PURPLE_COIN,
	//���S���̃R�C��
	WHITE_COIN,
	//������
	CURRENT_LIFE,
	//�ő吶����
	MAX_LIFE,
	//�U����
	ATTACK,
	//�ғőϐ�
	DEADLY_POISON_RESISTANCE,
	//�ғő����l
	DEADLY_POISON_VALUE,
	//�ғŒ~��
	DEADLY_POISON_ACCUMULATION,
	//��ბϐ�
	PARALYSIS_RESISTANCE,
	//��ბ����l
	PARALYSIS_VALUE,
	//��გ~��
	PARALYSIS_ACCUMULATION,
	//�Ö��ϐ�
	HYPNOSIS_RESISTANCE,
	//�Ö��ϐ�
	HYPNOSIS_VALUE,
	//�Ö��~��
	HYPNOSIS_ACCUMULATION,
	//�o���ϐ�
	BLOODING_RESISTANCE,
	//�o�������l
	BLOODING_VALUE,
	//�o���~��
	BLOODING_ACCUMULATION,
	//����
	BARGAINING_POWER,
	//���݂̃}�b�v���W
	CURRENT_MAP_X,
	CURRENT_MAP_Y,
};

enum ITEM_INFORMATION {
	MAP_X_,
	MAP_Y_,
	CURRENT_X_,
	CURRENT_Y_,
	DIRECTION_,
	EVENT_NO_,
	ITEM_TYPE_,
};

enum ACTION_COMMAND {
	//�����i�C�t
	KNIFE,
	//�n
	SLASH,
	//�V�[���h
	SHIELD,
	//��ԉ���
	ELIMINATION,
};
