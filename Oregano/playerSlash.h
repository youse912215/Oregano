#pragma once
#include "vec2.h"
#include <vector>
#include "dataSource.h"

class PlayerSlash {
private:

public:
	dVec2 slashPos; //�n���W

	void initialize(dVec2& pos);
	void slashCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& slash); //�n�̃N�[���_�E������
	void draw(DataSource& source); //�`�揈��

	PlayerSlash(); //�R���X�g���N�^
};
