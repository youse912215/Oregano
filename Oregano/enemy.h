#pragma once
#include "player.h"
#include "dataSource.h"
#include <vector>

using namespace std;

class Enemy {
private:
	Player& player; //�v���C���[�N���X����
	DataSource source;

	Vec2 pos; //�S�̃}�b�v�̍��W
	Vec2 center; //�S�̃}�b�v�̒��S���W
	Vec2 distance; //�v���C���[�Ƃ̋���
	Vec2 distanceSquared; //������2��
	Vec2 distanceNormalized; //���K����������
	Vec2 moveSpeed; //�ړ����x

	Vec2 screenPos; //��ʏ�̍��W
	Vec2 screenCenter; //��ʏ�̒��S���W
	Vec2 relativeDistance; //�v���C���[�Ƃ̑��΋���

	int attackPower;

	void draw(); //�`�揈��

	void getMoveSpeed(); //�ړ����x�擾
	void move(); //�ړ�����
	void dead(); //���S����

	void relativeDistanceUpdate(); //�v���C���[�Ƃ̑��΋����̍X�V

	void hitKnife(); //�i�C�t�q�b�g���̏���
	void hitSlash(); //�n�q�b�g���̏���

	void collision(); //�v���C���[�Ƃ̏Փ˔���

	void initPosition(); //�����ʒu�̎擾

	//�o���ʒu���擾
	double getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2);

	bool onScreenX(); //��ʏ��x���W�ɂ������
	bool onScreenY(); //��ʏ��y���W�ɂ������

	vector<int> coin;
	
	int attribute;
	vector<int> attributeValue;
	void getAttribute();

public:
	bool activity;
	bool alive;

	Enemy(Player& player);
	~Enemy();

	void update(); //�X�V����
};
