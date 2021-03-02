#pragma once
#include <vector>
#include "inputProcess.h"
#include "vec2.h"
#include "dataSource.h"

class PlayerKnife {
private:
	const double curvatureSpeed; //�Ȃ��鑬�x
	const double maxRange; //�i�C�t�̍ő�͈�

public:
	Vec2 knifePos; //�i�C�t���W
	Vec2 knifeAddPos; //�i�C�t�̉��Z���̍��W

	void initialize(Vec2& pos, Vec2& knifeCenter); //�i�C�t�̏�����
	void knifeCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag); //�i�C�t�̃N�[���_�E������
	void setKnifePosition(Vec2& pos); //�i�C�t�̃|�W�W�����Z�b�g
	void resetKnifePosition(Vec2& center, bool& knife); //�i�C�t�̃|�W�W�������Z�b�g
	void accelKnife(Input& input); //�i�C�t�̉���
	bool deleteKnife(Vec2& center); //�i�C�t�̍폜����
	void draw(DataSource& source); //�`�揈��

	PlayerKnife(); //�R���X�g���N�^
};
