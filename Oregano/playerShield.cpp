#include "playerShield.h"
#include "constant.h"
#include "DxLib.h"

PlayerShield::PlayerShield() :
	gaugePos(64, 16), shieldQuantity(4), addQuantity(4), cooldownMax(120),
	shieldPos(0.0, 0.0), value(0) {
}

/// <summary>
/// �V�[���h��ǉ��ŕt�^
/// </summary>
/// <param name="battleStyle">�퓬�X�^�C��</param>
/// <returns></returns>
int PlayerShield::addShield(const int& battleStyle) {
	//�퓬�X�^�C�����[�x�q(���z��)�̂Ƃ�
	if (battleStyle == CRAMPS) return addQuantity; //�V�[���h��ǉ�
	return 0;
}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">�v���C���[�̍��W</param>
void PlayerShield::initialize(Vec2d& pos) {
	shieldPos = pos;
}

/// <summary>
/// �V�[���h�̃N�[���_�E������
/// </summary>
void PlayerShield::countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag,
                                 std::vector<bool>& actionFlag) {
	if (cooldownFlag[SHIELD] && !actionFlag[SHIELD]) cooldown[SHIELD]++; //�N�[���_�E���J�n

	if (cooldown[SHIELD] >= cooldownMax) {
		cooldown[SHIELD] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[SHIELD] = false; //�N�[���_�E���t���O��false
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="source">�f�[�^�\�[�X</param>
void PlayerShield::draw(DataSource& source) {
	DrawGraph(static_cast<int>(shieldPos.dx), static_cast<int>(shieldPos.dy),
	          source.shieldGraph, true); //�V�[���h
	DrawRectGraph(static_cast<int>(shieldPos.dx), static_cast<int>(shieldPos.dy) - 10,
	              0, gaugePos.x * value - gaugePos.y, gaugePos.x, gaugePos.y,
	              source.shieldGauge, true, false, false); //�V�[���h�Q�[�W
}

/// <summary>
/// 0�ȉ���0�ɂ��鏈��
/// </summary>
void PlayerShield::zeroOut() {
	if (value <= 0) value = 0;
}

/// <summary>
/// �V�[���h��t�^
/// </summary>
/// <param name="battleStyle">�퓬�X�^�C��</param>
void PlayerShield::giveShield(const int& battleStyle) {
	value = shieldQuantity + addShield(battleStyle); //�V�[���h�ʂ�ǉ�
}
