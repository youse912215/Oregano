#pragma once
#include "player.h"
#include "dataSource.h"
#include "effectBlood.h"
#include <vector>

using namespace std;

class Enemy {
private:
	/* �`��֌W */
	Vec2d pos; //�S�̃}�b�v�̍��W
	Vec2d center; //�S�̃}�b�v�̒��S���W
	Vec2d screenCenter; //��ʏ�̒��S���W
	Vec2d relativeDistance; //�v���C���[�Ƃ̑��΋���
	const int lifeHeight; //���C�t�摜�̏c��

	/* �����n */
	void initPosition(Player& player); //�����ʒu�̎擾
	double getPopLocation(const int& mapDir, const int& coordinate1,
	                      const int& coordinate2); //�o���ʒu���擾
	void relativeDistanceUpdate(Player& player); //�v���C���[�Ƃ̑��΋����̍X�V
	void collision(Player& player); //�v���C���[�Ƃ̏Փ˔���

	void hitKnife(Player& player); //�i�C�t�q�b�g���̏���
	void hitSlash(); //�n�q�b�g���̏���

	void dead(); //���S����
	void countDeadTime(); //���S���Ԃ��J�E���g

	void draw(DataSource& source); //�`�揈��


	/* �X�e�[�^�X�֌W */
	vector<int> initLife; //�������C�t
	vector<int> possessionCoin; //�����R�C��
	vector<int> attackPower; //�U����
	vector<int> attributeValue; //�����l

	int life; //���C�t
	int pattern; //�o���p�^�[��
	int level; //���x��
	const int maxLevel; //�ő僌�x��

	void setStatus(Player& player); //�X�e�[�^�X��ݒ�
	void getAttribute(Player& player); //�����l���擾

	/* �_���[�W�֌W */
	vector<int> damageInterval; //�_���[�W�Ԋu
	vector<bool> damageFlag; //�_���[�W�t���O

	const double knifeRange; //�i�C�t�͈̔�
	const int deadTimeMax; //�ő厀�S����
	const int intervalMax; //�ő�Ԋu����

	void takeDamage(const int& act); //�_���[�W���󂯂�
	void damageProcess(Player& player, const int& act, DataSource& source); //�_���[�W����
	void noLife(Player& player); //0���C�t����


	/* ���T�[�W���֌W */
	Vec2d lissajousSpeed; //�ړ����x
	const double lissajousMaxTime; //���T�[�W���𐧌䂷�鎞��
	const double lissajousX; //���T�[�W������
	const double lissajousY; //���T�[�W���̏c��
	const double controlSpeed; //���䑬�x
	double lissajousTime; //���T�[�W���p�̎���
	int lissajousRandom; //���T�[�W���p�̃����_���ϐ�
	void countTime(); //���T�[�W���p�̃J�E���g����
	void lissajous(); //���T�[�W���Ȑ���`��

public:
	Vec2d screenPos; //��ʏ�̍��W

	int deadTime; //���S���ԁi�����܂ł̎��ԁj
	int attribute; //����
	bool activity; //�������
	bool deadFlag; //���S�t���O
	vector<bool> intervalFlag; //�Ԋu�t���O

	Enemy();
	~Enemy();

	void initialize(Player& player); //������
	void update(Player& player, DataSource& source); //�X�V����
};
