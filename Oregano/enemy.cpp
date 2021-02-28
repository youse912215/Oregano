#include "enemy.h"
#include "DxLib.h"
#include "constant.h"
#include "random.h"
#include <cmath>

#include "mapDraw.h"

Enemy::Enemy(int graph, Player& player) : player(player), graph(graph) {
	this->pos.dx = getPopLocation(ONE_MAP_X, 7/*get_random(4, TOTAL_MAPS_X - 1)*/, get_random(AREA_MIN, AREA_MAX));
	this->pos.dy = getPopLocation(ONE_MAP_Y, 7/*get_random(5, TOTAL_MAPS_Y - 1)*/, get_random(AREA_MIN, AREA_MAX));
	this->center = QUARTER_BLOCK_SIZE + pos;
	screenPos = 0;
	screenCenter = 0;
	relativeDistance = 0;

	attackPower = 5;

	activity = false;
	alive = true;
}

Enemy::~Enemy() {
}

/// <summary>
/// �`�揈��
/// </summary>
void Enemy::draw() {
	DrawGraph(static_cast<int>(screenPos.dx), static_cast<int>(screenPos.dy), graph, true); //�G
}

/// <summary>
/// �ړ�����
/// �v���C���[�̍����E���ňړ��������ω�����
/// </summary>
void Enemy::move() {
	/* x�����̈ړ� */
	if (screenPos.dx >= 0
		&& screenPos.dx < player.center.dx
		&& onScreenY()) {
		this->pos.dx += moveSpeed.dx; //�E��
	}
	else if (screenPos.dx >= player.center.dx
		&& screenPos.dx < WIN_WIDTH
		&& onScreenY()) {
		this->pos.dx -= moveSpeed.dx; //����
	}

	/* y�����̈ړ� */
	if (screenPos.dy >= 0
		&& screenPos.dy < player.center.dy
		&& onScreenX()) {
		this->pos.dy += moveSpeed.dy; //���
	}
	else if (screenPos.dy >= player.center.dy
		&& screenPos.dy < WIN_HEIGHT
		&& onScreenX()) {
		this->pos.dy -= moveSpeed.dy; //����
	}
}

/// <summary>
/// ���S����
/// </summary>
void Enemy::dead() {
	activity = false; //������Ԃ�false
	alive = false; //������Ԃ�false
}

/// <summary>
/// �v���C���[�Ƃ̑��΋����̍X�V
/// </summary>
void Enemy::relativeDistanceUpdate() {
	screenPos.dx = pos.dx - static_cast<double>(MapDraw::mapX); //��ʏ��x���W
	screenPos.dy = pos.dy - static_cast<double>(MapDraw::mapY); //��ʏ��y���W
	screenCenter = QUARTER_BLOCK_SIZE + screenPos; //��ʏ�̒��S���W
	relativeDistance = screenCenter - player.center; //�v���C���[�Ƃ̑��΋���

}

/// <summary>
/// �i�C�t�q�b�g���̏���
/// </summary>
void Enemy::hitKnife() {
	//�i�C�t�Ƃ̑��΋�����WEAPON_COLLISION_DISTANCE�ȉ��̂Ƃ�
	if (abs(screenCenter.dx - player.knifeCenter.dx) <= WEAPON_COLLISION_DISTANCE
		&& abs(screenCenter.dy - player.knifeCenter.dy) <= WEAPON_COLLISION_DISTANCE) {
		dead(); //���S����
	}
}

/// <summary>
/// �n�q�b�g���̏���
/// </summary>
void Enemy::hitSlash() {
	//
	if (abs(relativeDistance.dx) <= 80.0 && abs(relativeDistance.dy) <= 80.0) {
		dead(); //���S����
	}
}

/// <summary>
/// �v���C���[�Ƃ̏Փˏ���
/// </summary>
void Enemy::collision() {
	//�v���C���[�Ƃ̋�����ENEMY_COLLISION_DISTANCE�ȉ��̂Ƃ�
	if (abs(relativeDistance.dx) <= ENEMY_COLLISION_DISTANCE
		&& abs(relativeDistance.dy) <= ENEMY_COLLISION_DISTANCE) {
		dead(); //���S����
		player.lostPlayerCoin(attackPower);
	}
}

/// <summary>
/// �v���C���[�Ƃ̈ʒu�֌W����ړ����x�𓾂�
/// </summary>
void Enemy::getMoveSpeed() {
	distance = player.center - this->center; //����
	distanceSquared = distance * distance; //������2��
	distanceNormalized.dx = abs(distance.dx) / sqrt(distanceSquared.dx + distanceSquared.dy); //x�����̐��K��
	distanceNormalized.dy = abs(distance.dy) / sqrt(distanceSquared.dx + distanceSquared.dy); //y�����̐��K��
	moveSpeed = 4 * distanceNormalized; //�ړ����x
}

/// <summary>
/// ��ʏ��x���W�ɂ������
/// </summary>
bool Enemy::onScreenX() {
	return screenPos.dx >= 0 && screenPos.dx <= WIN_WIDTH;
}

/// <summary>
/// ��ʏ��y���W�ɂ������
/// </summary>
bool Enemy::onScreenY() {
	return screenPos.dy >= 0 && screenPos.dy <= WIN_HEIGHT;
}

/// <summary>
/// �����ʒu�̎擾
/// </summary>
void Enemy::initPosition() {
	pos.dx = getPopLocation(ONE_MAP_X, get_random(7, TOTAL_MAPS_X - 1), get_random(AREA_MIN, AREA_MAX)); //x���W
	pos.dy = getPopLocation(ONE_MAP_Y, get_random(8, TOTAL_MAPS_Y - 1), get_random(AREA_MIN, AREA_MAX)); //y���W
}

/// <summary>
/// �o���ʒu���擾
/// </summary>
/// <param name="mapDir">x�܂���y�̃}�b�v�T�C�Y</param>
/// <param name="coordinate1">�S�̃}�b�v�̍��W</param>
/// <param name="coordinate2">1���̍��W</param>
double Enemy::getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2) {
	return mapDir * coordinate1 + BLOCK_SIZE * coordinate2;
}

/// <summary>
/// �X�V����
/// </summary>
void Enemy::update() {
	relativeDistanceUpdate(); //�v���C���[�Ƃ̑��΋������擾

	if (player.knife) hitKnife(); //�i�C�t�����������Ƃ�
	if (player.slash) hitSlash(); //�n�����������Ƃ�

	//�G�������Ă���Ƃ�
	if (activity) {
		collision(); //�v���C���[�Ƃ̏Փˏ���
		getMoveSpeed(); //�ړ����x�擾
		move(); //�ړ�����
		draw(); //�`�揈��
	}
	else {
		initPosition(); //�����ʒu�̎擾
		if (abs(relativeDistance.dx) <= 500 || abs(relativeDistance.dy) <= 500 && alive) activity = true;
	}

	DrawFormatString(200, 185, GetColor(0, 0, 255),
	                 "En���W�F%lf, %lf",
	                 pos.dx, pos.dy, false);
	DrawFormatString(200, 200, GetColor(0, 0, 255),
	                 "�X�N���[�����W�F%lf, %lf",
	                 screenPos.dx, screenPos.dy, false);
	DrawFormatString(200, 215, GetColor(0, 0, 255),
	                 "���΍��W�F%lf, %lf",
	                 abs(relativeDistance.dx),
	                 abs(relativeDistance.dy), false);

}
