#pragma once
#include <vector>
#include "vec2.h"
#include "dataSource.h"

class PlayerShield {
private:
	Vec2 gaugePos;

	const int shieldQuantity; //�ʏ�̃V�[���h��
	const int addQuantity; //�ǉ��̃V�[���h��
	const int cooldownMax; //�ő�N�[���_�E��

	int addShield(const int& battleStyle); //�V�[���h��ǉ��ŕt�^

public:
	Vec2d shieldPos; //�V�[���h���W
	int value; //���݂̃V�[���h��

	void initialize(Vec2d& pos); //������
	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, std::vector<bool>& actionFlag);
	//�V�[���h�̃N�[���_�E������
	void draw(DataSource& source); //�`�揈��
	void zeroOut(); //0�ȉ���0�ɂ��鏈��
	void giveShield(const int& battleStyle); //�V�[���h��t�^

	PlayerShield();
};
