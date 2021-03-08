#include "playerKnife.h"
#include "DxLib.h"
#include <cmath>

PlayerKnife::PlayerKnife() :
	center(0.0, 0.0), radian(0.0), sign(0.0), curvatureSpeed(KNIFE_SPEED / 2.0),
	maxRange(BLOCK_SIZE * 3.0), reverseFlag(false), knifePos(0.0, 0.0), knifeAddPos(0.0, 0.0) {
}

/// <summary>
/// �`��p�̃��W�A���v�Z
/// </summary>
/// /// <param name="pos">�v���C���[���W</param>
void PlayerKnife::calculateRadian(Vec2d& pos) {
	changeDirection(pos); //�����ύX

	//���W�A�����v�Z���A�i�C�t�̈ʒu�ɂ���āAsign���ς��
	radian = atan2(this->center.dy - (pos.dy + HALF_BLOCK_SIZE_D),
	               abs(this->center.dx - (pos.dx + HALF_BLOCK_SIZE_D))) * sign;
}

/// <summary>
/// �����ύX
/// </summary>
/// <param name="pos">�v���C���[���W</param>
void PlayerKnife::changeDirection(Vec2d& pos) {
	//�i�C�t�̈ʒu���v���C���[��荶���ɂ���Ƃ�
	if (this->center.dx <= pos.dx + HALF_BLOCK_SIZE_D) {
		reverseFlag = true; //���]
		sign = -1.0; //���]
	}
		//�E���ɂ���Ƃ�
	else {
		reverseFlag = false; //�ʏ�
		sign = 1.0; //�ʏ�
	}
}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">�v���C���[�̍��W</param>
/// <param name="knifeCenter">�v���C���[�̒��S���W</param>
void PlayerKnife::initialize(Vec2d& pos, Vec2d& knifeCenter) {
	knifePos = pos + knifeAddPos; //�i�C�t�̍��W�̍X�V
	this->center = HALF_BLOCK_SIZE_D + knifePos; //�i�C�t�̒��S�ʒu�̍X�V
	knifeCenter = this->center; //�v���C���[�ɓn��
}

/// <summary>
/// �i�C�t�̃N�[���_�E������
/// </summary>
/// <param name="cooldown">�N�[���_�E��</param>
/// <param name="cooldownFlag">�N�[���_�E���t���O</param>
void PlayerKnife::countCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag) {
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
void PlayerKnife::setKnifePosition(Vec2d& pos) {
	/* x���� */
	if (knifePos.dx < pos.dx) knifeAddPos.dx -= KNIFE_SPEED;
	else if (knifePos.dx > pos.dx) knifeAddPos.dx += KNIFE_SPEED;
	else knifeAddPos.dx = 0.0;
	/* y���� */
	if (knifePos.dy < pos.dy) knifeAddPos.dy -= KNIFE_SPEED;
	else if (knifePos.dy > pos.dy)knifeAddPos.dy += KNIFE_SPEED;
	else knifeAddPos.dy = 0.0;
}

/// <summary>
/// �i�C�t�̃|�W�W���������Z�b�g����
/// </summary>
void PlayerKnife::resetKnifePosition(Vec2d& playerCenter, vector<bool>& actionFlag) {
	if (deleteKnife(playerCenter)) {
		actionFlag[KNIFE] = false;
		knifeAddPos = 0.0;
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
bool PlayerKnife::deleteKnife(Vec2d& playerCenter) {
	//�v���C���[����̋�����3�}�X������Ă��邩
	return abs(this->center.dx - playerCenter.dx) >= maxRange
		|| abs(this->center.dy - playerCenter.dy) >= maxRange;
}

/// <summary>
/// �`�揈��
/// �i�C�t�𐳂��������ŕ`�悷��
/// </summary>
/// <param name="source">�f�[�^�\�[�X</param>
void PlayerKnife::draw(DataSource& source) {
	DrawRotaGraph(static_cast<int>(this->center.dx),
	              static_cast<int>(this->center.dy),
	              1.0, radian,
	              source.knifeGraph, true, reverseFlag);


}
