#include "DxLib.h"
#include "eventBase.h"
#include "mapDraw.h"
#include "inputProcess.h"

char Input::keys[256] = {0};
char Input::oldkeys[256] = {0};


Input::Input() : buttonFlag(10) {
	A = false;
	B = false;
	X = false;
	Y = false;
	moveDirection = UP;
	mode = false;
}

void Input::inputInformation() {
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; ++i) {
		oldkeys[i] = keys[i];
	}
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}

void Input::padInformation() {
	pad = GetJoypadInputState(DX_INPUT_PAD1); //���͏�Ԏ擾
	padLeft = mode && (pad & PAD_INPUT_LEFT); //��
	padRight = mode && (pad & PAD_INPUT_RIGHT); //�E
	padUp = mode && (pad & PAD_INPUT_UP); //��
	padDown = mode && (pad & PAD_INPUT_DOWN); //��
	pad1 = mode && (pad & PAD_INPUT_1); //1(A)
	pad2 = mode && (pad & PAD_INPUT_2); //2(B)
	pad3 = mode && (pad & PAD_INPUT_3); //3(X)
	pad4 = mode && (pad & PAD_INPUT_4); //4(Y)
	pad5 = mode && (pad & PAD_INPUT_5); //5(LB)
	pad6 = mode && (pad & PAD_INPUT_6); //6(RB)
	pad7 = mode && (pad & PAD_INPUT_7); //7(VIEW)
	pad8 = mode && (pad & PAD_INPUT_8); //8(MENU)
	pad9 = mode && (pad & PAD_INPUT_9); //9(STICK_L)
	pad10 = mode && (pad & PAD_INPUT_10); //9(STICK_L)
}

void Input::inputModeChange() {
	if (keys[KEY_INPUT_M] && !oldkeys[KEY_INPUT_M]) mode = !mode ? true : false;
}

/// <summary>
/// �X�e�B�b�N�i�\���L�[�j�ړ�����
/// </summary>
void Input::moveProcess(const bool& collisionLeft, const bool& collisionRight,
                        const bool& collisionUp, const bool& collisionDown) {

	//���ړ�
	if (padLeft || !mode && keys[KEY_INPUT_LEFT]) {
		MapDraw::mapX -= MOVING_DISTANCE;
		if (collisionLeft) MapDraw::mapX += MOVING_DISTANCE;
		moveDirection = LEFT;
	}
	//�E�ړ�
	if (mode && padRight || !mode && keys[KEY_INPUT_RIGHT]) {
		MapDraw::mapX += MOVING_DISTANCE;
		if (collisionRight) MapDraw::mapX -= MOVING_DISTANCE;
		moveDirection = RIGHT;
	}
	//��ړ�
	if (mode && padUp || !mode && keys[KEY_INPUT_UP]) {
		MapDraw::mapY -= MOVING_DISTANCE;
		if (collisionUp) MapDraw::mapY += MOVING_DISTANCE;
		moveDirection = UP;
	}
	//���ړ�
	if (mode && padDown || !mode && keys[KEY_INPUT_DOWN]) {
		MapDraw::mapY += MOVING_DISTANCE;
		if (collisionDown) MapDraw::mapY -= MOVING_DISTANCE;
		moveDirection = DOWN;
	}

	DrawFormatString(0, 150, GetColor(255, 255, 120), "%d   %d",
	                 collisionLeft, collisionRight, false);
	DrawFormatString(0, 135, GetColor(255, 255, 120), "  %d",
	                 collisionUp, false);
	DrawFormatString(0, 165, GetColor(255, 255, 120), "  %d",
	                 collisionDown, false);


}

/// <summary>
/// �{�^�����͏���
/// </summary>
void Input::eventProcess() {
	//�L�����Z������
	if (pad1 || !mode && keys[KEY_INPUT_1]) A = true;
	else A = false;

	//����
	if (pad2 || !mode && keys[KEY_INPUT_2]) B = true;
	else B = false;

	//�������
	if (pad3 || !mode && keys[KEY_INPUT_3]) X = true;
	else X = false;

	//����
	if (pad4 || !mode && keys[KEY_INPUT_4]) Y = true;
	else Y = false;

	DrawFormatString(150, 150, GetColor(0, 255, 120), "%d   %d",
	                 X, B, false);
	DrawFormatString(150, 135, GetColor(0, 255, 120), "  %d",
	                 Y, false);
	DrawFormatString(150, 165, GetColor(0, 255, 120), "  %d",
	                 A, false);
}

/// <summary>
/// �I������
/// </summary>
void Input::endProcess() {
	if (pad8 || keys[KEY_INPUT_ESCAPE]) {
		EventBase::gameScene = END_SCENE;
	}
}

/// <summary>
/// �X�V����
/// </summary>
void Input::update() {
	inputInformation();
	padInformation();
	inputModeChange();
	eventProcess();
	endProcess();
}
