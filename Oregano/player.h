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
	Input& input; //���̓N���X
	MapDraw& draw_; //�}�b�v�`��N���X
	DataSource& source; //�f�[�^�\�[�X�N���X

	Vec2d pos; //�v���C���[���W

	vector<int> cooldown; //�A�N�V�����̃N�[���_�E��
	vector<bool> cooldownFlag; //�N�[���_�E���̃t���O

	bool damageFlag; //�_���[�W�t���O

	void draw(); //�`�揈��

	void actionCommand(); //�A�N�V�����R�}���h�̏���

	void knifeUpdate(); //�i�C�t�X�V����
	void slashUpdate(); //�n�X�V����
	void shieldUpdate(); //�V�[���h�X�V����
	void stateUpdate(); //��ԍX�V����

public:
	Vec2d center; //�v���C���[�̒��S���W
	Vec2d knifeCenter; //�i�C�t�̒��S���W
	Vec2d slashCenter; //�n�̒��S���W

	vector<bool> actionFlag; //�A�N�V�����t���O

	Player(Input& input, MapDraw& draw_, DataSource& source);
	~Player();

	int addDamage(const int& act); //�G�ւ̃_���[�W
	int currentMapPos(const int& pos); //���݂̃}�b�v��Ԃ�

	void lostPlayerCoin(const int& attackPower); //�R�C���̑�������
	void addPlayerCoin(const int& attribute, const int& enemyCoin); //�R�C���̒ǉ�����
	void addAttributeAccumulation(const int& attribute, const int& attributeValue); //�����l�̒~�Ϗ���
	void update(); //�X�V����
};
