#pragma once
#include "player.h"

class EnemyConclusion {
private:
	Player& player_; //�v���C���[�N���X
	DataSource source_; //�f�[�^�\�[�X�N���X

public:
	EnemyConclusion(Player& player_);

	void update(); //�X�V����
};
