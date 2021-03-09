#pragma once
#include "player.h"
#include "vec2.h"

class EnemyTracking {
private:
	Vec2d distance; //�v���C���[�Ƃ̋���
	Vec2d distanceSquared; //������2��
	Vec2d distanceNormalized; //���K����������
	Vec2d moveSpeed; //�ړ����x

	const int magnification; //�{��
	const int onLineDistance; //������̋���

	bool onScreenX(Vec2d& screenPos); //��ʏ��x���W�ɂ������
	bool onScreenY(Vec2d& screenPos); //��ʏ��y���W�ɂ������

	int moveOnLineX(Player& player, Vec2d& screenPos); //������̈ړ�(x����)
	int moveOnLineY(Player& player, Vec2d& screenPos); //������̈ړ�(y����)

	void getMoveSpeed(Player& player, Vec2d& pos); //�ړ����x�擾
	void move(Player& player, Vec2d& pos, Vec2d& screenPos); //�ړ�����

public:
	EnemyTracking();

	void update(Player& player, Vec2d& pos, Vec2d& screenPos); //�X�V����
};
