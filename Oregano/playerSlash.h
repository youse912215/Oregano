#pragma once
#include "vec2.h"
#include <vector>
#include "dataSource.h"

class PlayerSlash {
private:
	int drawTime; //�`�掞��
	const int graphNum; //�摜��
	const int graphWidth; //�摜��

public:
	Vec2d slashPos; //�n���W

	void initialize(Vec2d& pos); //������
	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& slash); //�n�̃N�[���_�E������
	void countTime(); //�`�掞�ԃJ�E���g
	void draw(DataSource& source); //�`�揈��

	PlayerSlash(); //�R���X�g���N�^
};
