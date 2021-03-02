#include "playerKnife.h"

#include <DxLib.h>

PlayerKnife::PlayerKnife() : curvatureSpeed(KNIFE_SPEED / 2.0), maxRange(BLOCK_SIZE * 3.0) {
	knifePos = 0; //�i�C�t���W
	knifeAddPos = 0; //�i�C�t�̉��Z���̍��W
}

/// <summary>
/// �i�C�t������
/// </summary>
void PlayerKnife::initialize(Vec2& pos, Vec2& knifeCenter) {
	knifePos = pos + knifeAddPos; //�i�C�t�̍��W�̍X�V
	knifeCenter = HALF_BLOCK_SIZE_D + knifePos; //�i�C�t�̒��S�ʒu�̍X�V
}

/// <summary>
/// �i�C�t�̃N�[���_�E������
/// </summary>
void PlayerKnife::knifeCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag) {
	if (cooldownFlag[KNIFE]) cooldown[KNIFE]++; //�N�[���_�E���J�n

	//�N�[���_�E����30�b
	if (cooldown[KNIFE] >= 30) {
		cooldown[KNIFE] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[KNIFE] = false; //�N�[���_�E���t���O��false
	}
}

/// <summary>
/// �i�C�t�̃|�W�W�������Z�b�g����
/// </summary>
void PlayerKnife::setKnifePosition(Vec2& pos) {
	/* x���� */
	if (knifePos.dx < pos.dx) knifeAddPos.dx -= KNIFE_SPEED;
	else if (knifePos.dx > pos.dx) knifeAddPos.dx += KNIFE_SPEED;
	else knifeAddPos.dx = 0;
	/* y���� */
	if (knifePos.dy < pos.dy) knifeAddPos.dy -= KNIFE_SPEED;
	else if (knifePos.dy > pos.dy)knifeAddPos.dy += KNIFE_SPEED;
	else knifeAddPos.dy = 0;
}

/// <summary>
/// �i�C�t�̃|�W�W���������Z�b�g����
/// </summary>
void PlayerKnife::resetKnifePosition(Vec2& center, bool& knife) {
	if (deleteKnife(center)) {
		knife = false;
		knifeAddPos.dx = 0.0;
		knifeAddPos.dy = 0.0;
	}
}

/// <summary>
/// �i�C�t�̉����i�W���C�p�b�h���ƋȂ��邱�Ƃ��\�j
/// �X�e�B�b�N�����ɑ΂��āA�Ȃ��鑬�x�����Z
/// </summary>
void PlayerKnife::accelKnife(Input& input) {
	/* x���� */
	if (input.STICK[LEFT]) knifeAddPos.dx -= curvatureSpeed;
	else if (input.STICK[RIGHT]) knifeAddPos.dx += curvatureSpeed;
	/* y���� */
	if (input.STICK[UP]) knifeAddPos.dy -= curvatureSpeed;
	else if (input.STICK[DOWN]) knifeAddPos.dy += curvatureSpeed;
}

/// <summary>
/// �i�C�t�̍폜����
/// </summary>
/// <returns></returns>
bool PlayerKnife::deleteKnife(Vec2& center) {
	//�v���C���[����̋�����3�}�X������Ă��邩
	return abs(knifePos.dx + HALF_BLOCK_SIZE_D - center.dx) >= maxRange
		|| abs(knifePos.dy + HALF_BLOCK_SIZE_D - center.dy) >= maxRange;
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="source">�f�[�^�\�[�X</param>
void PlayerKnife::draw(DataSource& source) {
	DrawGraph(static_cast<int>(knifePos.dx), static_cast<int>(knifePos.dy), source.knifeGraph, true);
}
