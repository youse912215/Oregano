#pragma once
#include <vector>
#include "vec2.h"
#include "dataSource.h"

class PlayerShield {
private:

public:
	Vec2d shieldPos; //�V�[���h���W
	int value; //�V�[���h��

	void initialize(Vec2d& pos); //������
	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& shield); //�V�[���h�̃N�[���_�E������
	void draw(DataSource& source); //�`�揈��
	void zeroOut(); //0�ȉ���0�ɂ��鏈��

	PlayerShield();
};
