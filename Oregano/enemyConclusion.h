#pragma once
#include "player.h"

class EnemyConclusion {
private:
	Player& player_; //�v���C���[�N���X
	DataSource source_; //�f�[�^�\�[�X�N���X

public:
	void update(); //�X�V����

	EnemyConclusion(Player& player_);
};
