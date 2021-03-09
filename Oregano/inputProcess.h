#pragma once
#include "DxLib.h"
#include "mapCollision.h"
#include "mapDraw.h"
#include "moveProcess.h"
#include <vector>

using namespace std;

class Input {
private:
	MoveProcess move_; //�ړ������N���X

	static char oldkeys[256]; //�O�̃L�[���͂̏��
	static char keys[256]; //�L�[���͂̏��

	int oldPad; //�O�̃L�[���͂̏��
	int pad; //�L�[���͂̏��

	bool mode; //���̓��[�h

	vector<bool> padNum; //�W���C�p�b�h�ԍ�
	vector<bool> oldPadNum;
	vector<bool> inputButton; //���̓{�^��

	bool getInputButton(const int& buttonName); //�{�^�����͂�Ԃ�

	void directionProcess(const int& dir); //��������
	void keyboardInformation(); //�L�[�{�[�h���
	void padsInformation(); //�W���C�p�b�h���
	void eventProcess(); //�{�^�����͏���

public:
	/* �e�{�^���t���O */
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool VIEW;
	bool MENU;

	vector<bool> buttonFlag; //�{�^���t���O
	vector<bool> stickFlag; //�X�e�B�b�N�t���O
	bool anySTICK(); //�����ꂩ�̃X�e�B�b�N��Ԃ�Ԃ�

	int device; //���݂̃f�o�C�X
	int moveDirection; //�����Ă���ړ�����

	Input(); //�R���X�g���N�^

	void deviceModeChange(); //�L�[�{�[�h�ƃW���C�p�b�h��؂�ւ���
	void movement(MapCollision& collision, MapDraw& draw); //���͏���
	void menuProcess(); //���j���[����
	void update(); //�X�V����
};
