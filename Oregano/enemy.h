#pragma once
#include "player.h"
#include "dataSource.h"
#include "effectBlood.h"
#include <vector>
#include "player.h"
#include "inputProcess.h"


using namespace std;

class Enemy {
private:
	//Player player(Input input); //�v���C���[�N���X����
	DataSource source;

	Vec2d pos; //�S�̃}�b�v�̍��W
	Vec2d center; //�S�̃}�b�v�̒��S���W
	Vec2d screenCenter; //��ʏ�̒��S���W


	Vec2d relativeDistance; //�v���C���[�Ƃ̑��΋���

	void draw(); //�`�揈��

	void dead(); //���S����

	void relativeDistanceUpdate(Player& player); //�v���C���[�Ƃ̑��΋����̍X�V

	void hitKnife(Player& player); //�i�C�t�q�b�g���̏���
	void hitSlash(Player& player); //�n�q�b�g���̏���

	void collision(Player& player); //�v���C���[�Ƃ̏Փ˔���

	void initPosition(); //�����ʒu�̎擾

	//�o���ʒu���擾
	double getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2);

	void countDeadTime(); //���S���Ԃ��J�E���g

	vector<int> coin; //�R�C��
	vector<int> attackPower; //�U����
	int level; //���x��


	vector<int> attributeValue;
	void getAttribute(); //�����𞡟L��
	void getLevel(); //���x�����擾


	void countTime(); //���T�[�W���p�̃J�E���g����
	void lissajous(); //���T�[�W���Ȑ���`��
	Vec2d moveSpeed2; //�ړ����x
	double lissajousTime; //���T�[�W���p�̎���
	int lissajousRandom; //���T�[�W���p�̃����_���ϐ�

	int pattern;

public:
	Vec2d screenPos; //��ʏ�̍��W

	int attribute;
	bool activity;
	bool deadFlag;
	int deadTime;


	Enemy();
	~Enemy();


	void update(Player& player); //�X�V����
	void initialize(Player& player);
};
