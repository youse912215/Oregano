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
	activity = false;
	alive = true;
}

Enemy::~Enemy() {
}

/// <summary>
/// �`�揈��
/// </summary>
void Enemy::draw() {
	DrawGraph(static_cast<int>(screenPosX()), static_cast<int>(screenPosY()), graph, true);
}

/// <summary>
/// �ړ�����
/// �v���C���[�̍����E���ňړ��������ω�����
/// </summary>
void Enemy::move() {
	/* x�����̈ړ� */
	if (screenPosX() >= 0
		&& screenPosX() < player.center.dx
		&& onScreenY()) {
		this->pos.dx += moveSpeed.dx; //�E��
	}
	else if (screenPosX() >= player.center.dx
		&& screenPosX() < WIN_WIDTH
		&& onScreenY()) {
		this->pos.dx -= moveSpeed.dx; //����
	}

	/* y�����̈ړ� */
	if (screenPosY() >= 0
		&& screenPosY() < player.center.dy
		&& onScreenX()) {
		this->pos.dy += moveSpeed.dy; //���
	}
	else if (screenPosY() >= player.center.dy
		&& screenPosY() < WIN_HEIGHT
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
/// �i�C�t�����������Ƃ�
/// </summary>
void Enemy::hitKnife() {
	if (abs(screenPosX() + (HALF_BLOCK_SIZE / 2.0) - player.knifeCenter.dx) <= WEAPON_COLLISION_DISTANCE
		&& abs(screenPosY() + (HALF_BLOCK_SIZE / 2.0) - player.knifeCenter.dy) <= WEAPON_COLLISION_DISTANCE) {
		dead(); //���S����
	}
}

/// <summary>
/// �n�����������Ƃ�
/// </summary>
void Enemy::hitSlash() {
	if (relativeDistanceX() <= 80.0 && relativeDistanceY() <= 80.0) dead(); //���S����
}

/// <summary>
/// �v���C���[�Ƃ̏Փˏ���
/// </summary>
void Enemy::collision() {
	//�v���C���[�Ƃ̋�����ENEMY_COLLISION_DISTANCE�ȉ��̂Ƃ�
	if (relativeDistanceX() <= ENEMY_COLLISION_DISTANCE
		&& relativeDistanceY() <= ENEMY_COLLISION_DISTANCE) {
		dead(); //���S����
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
/// ��ʏ��x���W
/// </summary>
double Enemy::screenPosX() {
	return pos.dx - static_cast<double>(MapDraw::mapX);
}

/// <summary>
/// ��ʏ��y���W
double Enemy::screenPosY() {
	return pos.dy - static_cast<double>(MapDraw::mapY);
}

/// <summary>
/// �v���C���[�Ƃ̑��΋����ix�����j
/// </summary>
double Enemy::relativeDistanceX() {
	return abs(screenPosX() + QUARTER_BLOCK_SIZE - player.center.dx);
}

/// <summary>
/// �v���C���[�Ƃ̑��΋����iy�����j
/// </summary>
double Enemy::relativeDistanceY() {
	return abs(screenPosY() + QUARTER_BLOCK_SIZE - player.center.dy);
}

/// <summary>
/// ��ʏ��x���W�ɂ������
/// </summary>
bool Enemy::onScreenX() {
	return screenPosX() >= 0 && screenPosX() <= WIN_WIDTH;
}

/// <summary>
/// ��ʏ��y���W�ɂ������
/// </summary>
bool Enemy::onScreenY() {
	return screenPosY() >= 0 && screenPosY() <= WIN_HEIGHT;
}

/// <summary>
/// �����ʒu�̎擾
/// </summary>
void Enemy::initPosition() {
	pos.dx = getPopLocation(ONE_MAP_X, get_random(7, TOTAL_MAPS_X - 1), get_random(AREA_MIN, AREA_MAX));
	pos.dy = getPopLocation(ONE_MAP_Y, get_random(8, TOTAL_MAPS_Y - 1), get_random(AREA_MIN, AREA_MAX));
}

/// <summary>
/// 
/// </summary>
/// <param name="mapDir">x�܂���y�̃}�b�v�T�C�Y</param>
/// <param name="coordinate1">�S�̃}�b�v�̍��W</param>
/// <param name="coordinate2">1���̍��W</param>
/// <returns></returns>
double Enemy::getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2) {
	return mapDir * coordinate1 + BLOCK_SIZE * coordinate2;
}

/// <summary>
/// �X�V����
/// </summary>
void Enemy::update() {
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
		if (relativeDistanceX() <= 500 || relativeDistanceY() <= 500 && alive) activity = true;
	}

	DrawFormatString(200, 185, GetColor(0, 0, 255),
	                 "En���W�F%lf, %lf",
	                 pos.dx, pos.dy, false);
	DrawFormatString(200, 200, GetColor(0, 0, 255),
	                 "�X�N���[�����W�F%lf, %lf",
	                 relativeDistanceX(), relativeDistanceY(), false);
	DrawFormatString(200, 215, GetColor(0, 0, 255),
	                 "���΍��W�F%lf, %lf",
	                 abs(screenPosX() + (HALF_BLOCK_SIZE / 2.0) - player.knifeCenter.dx),
	                 abs(screenPosY() + (HALF_BLOCK_SIZE / 2.0) - player.knifeCenter.dy), false);

}
