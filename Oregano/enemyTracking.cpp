#include "enemyTracking.h"

EnemyTracking::EnemyTracking() :
	distance(0.0, 0.0), distanceSquared(0.0, 0.0), distanceNormalized(0.0, 0.0), moveSpeed(0.0, 0.0) {
}

/// <summary>
/// �ړ����x���擾
/// </summary>
void EnemyTracking::getMoveSpeed(Player& player, Vec2d& pos) {
	distance = player.center - (QUARTER_BLOCK_SIZE_D + pos); //����
	distanceSquared = distance * distance; //������2��
	distanceNormalized.dx = abs(distance.dx) / sqrt(distanceSquared.dx + distanceSquared.dy); //x�����̐��K��
	distanceNormalized.dy = abs(distance.dy) / sqrt(distanceSquared.dx + distanceSquared.dy); //y�����̐��K��
	moveSpeed = 4 * distanceNormalized; //�ړ����x
}

/// <summary>
/// �ړ�����
/// �v���C���[�̍����E���ňړ��������ω�����
/// </summary>
void EnemyTracking::move(Player& player, Vec2d& pos, Vec2d& screenPos) {
	/* x�����̈ړ� */
	if (screenPos.dx >= 0
		&& screenPos.dx < player.center.dx
		&& onScreenY(screenPos)) {
		pos.dx += moveSpeed.dx; //�E��
	}
	else if (screenPos.dx >= player.center.dx
		&& screenPos.dx < WIN_WIDTH
		&& onScreenY(screenPos)) {
		pos.dx -= moveSpeed.dx; //����
	}

	/* y�����̈ړ� */
	if (screenPos.dy >= 0
		&& screenPos.dy < player.center.dy
		&& onScreenX(screenPos)) {
		pos.dy += moveSpeed.dy; //���
	}
	else if (screenPos.dy >= player.center.dy
		&& screenPos.dy < WIN_HEIGHT
		&& onScreenX(screenPos)) {
		pos.dy -= moveSpeed.dy; //����
	}
}

/// <summary>
/// ��ʏ��x���W�ɂ������
/// </summary>
bool EnemyTracking::onScreenX(Vec2d& screenPos) {
	return screenPos.dx >= 0 && screenPos.dx <= WIN_WIDTH;
}

/// <summary>
/// ��ʏ��y���W�ɂ������
/// </summary>
bool EnemyTracking::onScreenY(Vec2d& screenPos) {
	return screenPos.dy >= 0 && screenPos.dy <= WIN_HEIGHT;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="player">�v���C���[�N���X</param>
/// <param name="pos">�G�̍��W</param>
/// <param name="screenPos">�G�̉�ʏ���W</param>
void EnemyTracking::update(Player& player, Vec2d& pos, Vec2d& screenPos) {
	getMoveSpeed(player, pos); //�ړ����x�̎擾
	move(player, pos, screenPos); //�ړ�����
}
