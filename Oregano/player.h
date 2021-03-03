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
	DataSource source; //�f�[�^�\�[�X�N���X����

	Vec2d pos; //�v���C���[���W


	vector<int> cooldown; //�A�N�V�����̃N�[���_�E��
	vector<bool> cooldownFlag; //�N�[���_�E���̃t���O

	void draw(); //�`�揈��

	void actionCommand(); //�A�N�V�����R�}���h�̏���


	void knifeUpdate(); //�i�C�t�X�V����
	void slashUpdate(); //�n�X�V����
	void shieldUpdate(); //�V�[���h�X�V����

	void coinUpdate();
	vector<int> coin;

	vector<int> attributeAccumulation; //�����ϋv�l

	int battleStyle; //�퓬�X�^�C���i0:�ԖG�K, 1:�[�x�q, 2:���q��, 3:���g�ԁj
	void changeBattleStyle(const int& dir); //�퓬�X�^�C����؂�ւ���
	void battleStyleUpdate();

	vector<bool> stateAbnormal; //��Ԉُ�i0:�ғŁA1:�z���A2:�����A3:�o���j


public:
	Vec2d center; //�v���C���[�̒��S���W
	Vec2d knifeCenter; //�i�C�t�̒��S���W
	Vec2d slashCenter; //�n�̒��S���W

	bool knife;
	bool slash;
	bool shield;

	void lostPlayerCoin(const int& attackPower); //�R�C���̑�������
	void addPlayerCoin(const int& attribute, const int& enemyCoin); //�R�C���̒ǉ�����

	void addAttributeAccumulation(const int& attribute, const int& attributeValue);

	vector<int> status;
	vector<int> possessionItem;
	vector<int> possessionAccessory;
	vector<int> possessionJewel;
	vector<int> possessionMineral;

	Player(Input& input);
	~Player();

	void update(); //�X�V����
};

//----------------------------------------------------------------------------------//
