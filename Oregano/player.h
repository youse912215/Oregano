#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"
#include <vector>

using namespace std;

//�v���C���[
class Player {
private:
	Input& input; //���̓N���X����
	DataSource& source; //�f�[�^�\�[�X�N���X����

	Vec2 pos; //�v���C���[���W
	Vec2 knifePos; //�i�C�t���W
	Vec2 knifeAddPos; //�i�C�t�̉��Z���̍��W
	Vec2 slashPos; //�n���W

	vector<int> cooldown; //�A�N�V�����̃N�[���_�E��
	vector<bool> cooldownFlag; //�N�[���_�E���̃t���O

	void draw(); //�`�揈��

	void actionCommand(); //�A�N�V�����R�}���h�̏���

	void knifeCooldown();
	void knifePositionSet(); //�i�C�t�̃|�W�W�����Z�b�g
	void knifePositionReset(); //�i�C�t�̃|�W�W�������Z�b�g
	void accelKnife(); //�i�C�t�̉���
	void knifeUpdate(); //�i�C�t�̍X�V����
	bool deleteKnife(); //�i�C�t�̍폜����

	void slashCooldown();
	void slashUpdate();


public:
	Vec2 center; //�v���C���[�̒��S���W
	Vec2 knifeCenter; //�i�C�t�̒��S���W
	Vec2 slashCenter; //�n�̒��S���W

	bool knife;
	bool slash;

	vector<int> status;
	vector<int> possessionItem;
	vector<int> possessionAccessory;
	vector<int> possessionJewel;
	vector<int> possessionMineral;

	Player(Input& input, DataSource& source);
	~Player();

	void update(); //�X�V����
};
