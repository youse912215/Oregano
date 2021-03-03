#pragma once
#include <vector>
#include "vec2.h"
#include "dataSource.h"

class PlayerShield {
private:

public:
	dVec2 shieldPos; //�V�[���h���W
	int shieldValue; //�V�[���h��

	void initialize(dVec2& pos);
	void shieldCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& shield); //�V�[���h�̃N�[���_�E������
	void draw(DataSource& source);

	PlayerShield();
};
