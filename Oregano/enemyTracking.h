#pragma once
#include "player.h"
#include "vec2.h"

class EnemyTracking {
private:

public:
	Vec2d distance; //�v���C���[�Ƃ̋���
	Vec2d distanceSquared; //������2��
	Vec2d distanceNormalized; //���K����������
	Vec2d moveSpeed; //�ړ����x

	EnemyTracking();

	void getMoveSpeed(Player& player, Vec2d& pos); //�ړ����x�擾
	void move(Player& player, Vec2d& pos, Vec2d& screenPos); //�ړ�����

	bool onScreenX(Vec2d& screenPos); //��ʏ��x���W�ɂ������
	bool onScreenY(Vec2d& screenPos); //��ʏ��y���W�ɂ������

	void update(Player& player, Vec2d& pos, Vec2d& screenPos); //�X�V����
};
