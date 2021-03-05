#pragma once
#include "player.h"
#include "dataSource.h"
#include "effectBlood.h"
#include <vector>

using namespace std;

class Enemy {
private:
	Vec2d pos; //�S�̃}�b�v�̍��W
	Vec2d center; //�S�̃}�b�v�̒��S���W
	Vec2d screenCenter; //��ʏ�̒��S���W

	Vec2d relativeDistance; //�v���C���[�Ƃ̑��΋���


	void draw(DataSource& source); //�`�揈��

	void dead(); //���S����

	void relativeDistanceUpdate(Player& player); //�v���C���[�Ƃ̑��΋����̍X�V

	void hitKnife(Player& player); //�i�C�t�q�b�g���̏���
	void hitSlash(); //�n�q�b�g���̏���

	void collision(Player& player); //�v���C���[�Ƃ̏Փ˔���

	void initPosition(Player& player); //�����ʒu�̎擾

	//�o���ʒu���擾
	double getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2);

	void countDeadTime(); //���S���Ԃ��J�E���g

	int life; //���C�t
	vector<int> initLife; //�������C�t
	vector<int> possessionCoin; //�����R�C��
	vector<int> attackPower; //�U����
	int level; //���x��

	vector<int> damageInterval; //�_���[�W�Ԋu
	vector<bool> damageFlag; //�_���[�W�t���O
	void takeDamage(const int& act); //�_���[�W���󂯂�
	void damageProcess(Player& player, const int& act); //�_���[�W����
	void noLife(Player& player); //0���C�t����

	vector<int> attributeValue;
	void setStatus(); //�X�e�[�^�X��ݒ�

	Vec2d lissajousSpeed; //�ړ����x
	const double lissajousMaxTime; //���T�[�W���𐧌䂷�鎞��
	const double lissajousX; //���T�[�W������
	const double lissajousY; //���T�[�W���̏c��
	const double controlSpeed; //���䑬�x
	double lissajousTime; //���T�[�W���p�̎���
	int lissajousRandom; //���T�[�W���p�̃����_���ϐ�
	void countTime(); //���T�[�W���p�̃J�E���g����
	void lissajous(); //���T�[�W���Ȑ���`��

	int pattern; //�o���p�^�[��

public:
	Vec2d screenPos; //��ʏ�̍��W

	int deadTime; //���S���ԁi�����܂ł̎��ԁj
	int attribute; //����
	bool activity; //�������
	bool deadFlag; //���S�t���O
	vector<bool> intervalFlag; //�Ԋu�t���O

	Enemy();
	~Enemy();

	void update(Player& player, DataSource& source); //�X�V����
	void initialize(Player& player);
};
