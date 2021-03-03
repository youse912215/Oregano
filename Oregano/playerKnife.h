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
	dVec2 knifePos; //�i�C�t���W
	dVec2 knifeAddPos; //�i�C�t�̉��Z���̍��W

	void initialize(dVec2& pos, dVec2& knifeCenter); //�i�C�t�̏�����
	void knifeCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag); //�i�C�t�̃N�[���_�E������
	void setKnifePosition(dVec2& pos); //�i�C�t�̃|�W�W�����Z�b�g
	void resetKnifePosition(dVec2& center, bool& knife); //�i�C�t�̃|�W�W�������Z�b�g
	void accelKnife(Input& input); //�i�C�t�̉���
	bool deleteKnife(dVec2& center); //�i�C�t�̍폜����
	void draw(DataSource& source); //�`�揈��

	PlayerKnife(); //�R���X�g���N�^
};
