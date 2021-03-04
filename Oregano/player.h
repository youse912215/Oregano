#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "mapDraw.h"
#include "dataSource.h"
#include <vector>

using namespace std;

//�v���C���[
class Player {
private:
	Input& input; //���̓N���X����
	MapDraw& draw_;
	DataSource source; //�f�[�^�\�[�X�N���X����

	Vec2d pos; //�v���C���[���W

	vector<int> coin; //�R�C���iHP�A�U���̖����j
	vector<int> cooldown; //�A�N�V�����̃N�[���_�E��
	vector<bool> cooldownFlag; //�N�[���_�E���̃t���O

	void draw(); //�`�揈��

	void actionCommand(); //�A�N�V�����R�}���h�̏���


	void knifeUpdate(); //�i�C�t�X�V����
	void slashUpdate(); //�n�X�V����
	void shieldUpdate(); //�V�[���h�X�V����
	void stateAbnormalUpdate(); //��Ԉُ�X�V����

	bool state(const int& num);
	bool cool(const int& num);

public:
	Vec2d center; //�v���C���[�̒��S���W
	Vec2d knifeCenter; //�i�C�t�̒��S���W
	Vec2d slashCenter; //�n�̒��S���W

	bool knife;
	bool slash;
	bool shield;
	bool elimination;

	void lostPlayerCoin(const int& attackPower); //�R�C���̑�������
	void addPlayerCoin(const int& attribute, const int& enemyCoin); //�R�C���̒ǉ�����
	void addAttributeAccumulation(const int& attribute, const int& attributeValue); //�����l�̒~�Ϗ���

	vector<int> status;
	vector<int> possessionItem;
	vector<int> possessionAccessory;
	vector<int> possessionJewel;
	vector<int> possessionMineral;

	Player(Input& input, MapDraw& draw_);
	~Player();

	void update(); //�X�V����
};

//----------------------------------------------------------------------------------//
