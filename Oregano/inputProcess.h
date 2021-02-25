#pragma once
#include "DxLib.h"
#include "mapCollision.h"
#include <vector>

using namespace std;

class Input {
private:
	static char oldkeys[256]; //�O�̃L�[���͂̏��
	static char keys[256]; //�L�[���͂̏��

	int oldPad; //�O�̃L�[���͂̏��
	int pad; //�L�[���͂̏��

	bool mode; //���̓��[�h

	vector<bool> padNum; //�W���C�p�b�h�ԍ�
	vector<bool> inputButton; //���̓{�^��

	bool getInputButton(const int& buttonName); //�{�^�����͂�Ԃ�

public:
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;

	int moveDirection; //�����Ă���ړ�����

	vector<bool> buttonFlag; //�{�^���t���O

	Input(); //�R���X�g���N�^

	void keyboardInformation(); //�L�[�{�[�h���
	void padsInformation(); //�W���C�p�b�h���
	void inputModeChange(); //�L�[�{�[�h�ƃW���C�p�b�h��؂�ւ���
	void moveProcess(MapCollision& collision); //���͏���
	void eventProcess(); //�{�^�����͏���
	void endProcess(); //�I������
	void update(); //�X�V����
};
