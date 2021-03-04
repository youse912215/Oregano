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
	void inputModeChange(); //�L�[�{�[�h�ƃW���C�p�b�h��؂�ւ���
	void eventProcess(); //�{�^�����͏���
	void endProcess(); //�I������

public:
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;

	vector<bool> buttonFlag; //�{�^���t���O
	vector<bool> STICK;
	bool anySTICK();

	int moveDirection; //�����Ă���ړ�����

	Input(); //�R���X�g���N�^

	void movement(MapCollision& collision, MapDraw& draw); //���͏���
	void update(); //�X�V����
};
