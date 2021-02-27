#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"
#include <vector>

using namespace std;

//�v���C���[
class Player {
private:
	Input& input;
	DataSource& source;
	Vec2 knifePosition;

	vector<int> cooldown; //�A�N�V�����̃N�[���_�E��
	vector<bool> cooldownFlag; //�N�[���_�E���̃t���O

	void draw(); //�`�揈��

	void actionCommand(); //�A�N�V�����R�}���h�̏���

	void knifePositionSet(); //�i�C�t�̃|�W�W�����Z�b�g
	void knifePositionReset(); //�i�C�t�̃|�W�W�������Z�b�g
	void accelKnife(); //�i�C�t�̉���
	void knifeUpdate(); //�i�C�t�̍X�V����
	bool deleteKnife(); //�i�C�t�̍폜����


public:
	Vec2 pos;
	Vec2 center;

	Vec2 knifePos;
	Vec2 knifeCenter;

	bool knife;
	bool rotatingSlash;

	vector<int> status;
	vector<int> possessionItem;
	vector<int> possessionAccessory;
	vector<int> possessionJewel;
	vector<int> possessionMineral;

	Player(Input& input, DataSource& source);
	~Player();

	void update();
};
