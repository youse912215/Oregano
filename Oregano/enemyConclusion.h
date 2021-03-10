#pragma once
#include "player.h"

class EnemyConclusion {
private:
	Player& player_; //�v���C���[�N���X
	DataSource& source_; //�f�[�^�\�[�X�N���X

	const int showTime; //�ő�̕\������

public:
	EnemyConclusion(Player& player_, DataSource& source_);

	void update(); //�X�V����
};
