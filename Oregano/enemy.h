#pragma once
#include "player.h"
#include "dataSource.h"
#include "effectParticle.h"
#include <vector>
#include "player.h"
#include "inputProcess.h"


using namespace std;

class Enemy {
private:
	//Player player(Input input); //�v���C���[�N���X����
	DataSource source;

	Vec2 pos; //�S�̃}�b�v�̍��W
	Vec2 center; //�S�̃}�b�v�̒��S���W
	Vec2 distance; //�v���C���[�Ƃ̋���
	Vec2 distanceSquared; //������2��
	Vec2 distanceNormalized; //���K����������
	Vec2 moveSpeed; //�ړ����x
	Vec2 screenCenter; //��ʏ�̒��S���W


	Vec2 relativeDistance; //�v���C���[�Ƃ̑��΋���

	int attackPower;

	void draw(); //�`�揈��

	void getMoveSpeed(Player& player); //�ړ����x�擾
	void move(Player& player); //�ړ�����
	void dead(); //���S����

	void relativeDistanceUpdate(Player& player); //�v���C���[�Ƃ̑��΋����̍X�V

	void hitKnife(Player& player); //�i�C�t�q�b�g���̏���
	void hitSlash(Player& player); //�n�q�b�g���̏���

	void collision(Player& player); //�v���C���[�Ƃ̏Փ˔���

	void initPosition(); //�����ʒu�̎擾

	//�o���ʒu���擾
	double getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2);

	bool onScreenX(); //��ʏ��x���W�ɂ������
	bool onScreenY(); //��ʏ��y���W�ɂ������

	vector<int> coin;

	int attribute;
	vector<int> attributeValue;
	void getAttribute();

	void countDeadTime();

	void lissajous();
	Vec2 movePattern2;
	double lissajousTime;
	int lissajousRandom;

public:
	bool activity;
	bool deadFlag;
	int deadTime;
	Vec2 screenPos; //��ʏ�̍��W

	Enemy();
	~Enemy();


	void update(Player& player); //�X�V����
	void initProcess(Player& player);
};
