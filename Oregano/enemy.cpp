#include "enemy.h"
#include "DxLib.h"
#include "constant.h"
#include "random.h"
#include "mapDraw.h"
#include <cmath>

#include "enemyTracking.h"

EnemyTracking tracking;


Enemy::Enemy() :
	pos(0.0, 0.0), center(0.0, 0.0),
	screenCenter(0.0, 0.0), relativeDistance(0.0, 0.0),

	coin{5, 15, 25}, attackPower{5, 25, 50}, level(0), attributeValue{15, 30, 50}, lissajousTime(0),

	lissajousRandom(0), pattern(0),

	screenPos(0.0, 0.0), attribute(0),

	activity(false), deadFlag(false), deadTime(0) {

}

Enemy::~Enemy() {
}

/// <summary>
/// �`�揈��
/// </summary>
void Enemy::draw(DataSource& source) {
	//DrawGraph(static_cast<int>(screenPos.dx), static_cast<int>(screenPos.dy), graph, true); //�G

	//�����iattribute�j�ɂ���āA�摜��ύX����
	DrawRectGraph(static_cast<int>(screenPos.dx),
	              static_cast<int>(screenPos.dy),
	              attribute * static_cast<int>(HALF_BLOCK_SIZE_D), 0,
	              static_cast<int>(HALF_BLOCK_SIZE_D), static_cast<int>(HALF_BLOCK_SIZE_D),
	              source.enemyGraph, true, false);
}

/// <summary>
/// ���S����
/// </summary>
void Enemy::dead() {
	deadFlag = true;
	activity = false; //������Ԃ�false
}

/// <summary>
/// �v���C���[�Ƃ̑��΋����̍X�V
/// </summary>
void Enemy::relativeDistanceUpdate(Player& player) {
	screenPos.dx = pos.dx - static_cast<double>(MapDraw::mapX); //��ʏ��x���W
	screenPos.dy = pos.dy - static_cast<double>(MapDraw::mapY); //��ʏ��y���W
	screenCenter = QUARTER_BLOCK_SIZE_D + screenPos; //��ʏ�̒��S���W
	relativeDistance = screenCenter - player.center; //�v���C���[�Ƃ̑��΋���

}

/// <summary>
/// �i�C�t�q�b�g���̏���
/// </summary>
void Enemy::hitKnife(Player& player) {
	//�i�C�t�Ƃ̑��΋�����WEAPON_COLLISION_DISTANCE�ȉ��̂Ƃ�
	if (abs(screenCenter.dx - player.knifeCenter.dx) <= WEAPON_COLLISION_DISTANCE
		&& abs(screenCenter.dy - player.knifeCenter.dy) <= WEAPON_COLLISION_DISTANCE) {
		dead(); //���S����
		player.addPlayerCoin(attribute, this->coin[level]); //�R�C���ǉ�����
	}
}

/// <summary>
/// �n�q�b�g���̏���
/// </summary>
void Enemy::hitSlash(Player& player) {
	//
	if (abs(relativeDistance.dx) <= 80.0 && abs(relativeDistance.dy) <= 80.0) {
		dead(); //���S����
		player.addPlayerCoin(attribute, this->coin[level]); //�R�C���ǉ�����
	}
}

/// <summary>
/// �v���C���[�Ƃ̏Փˏ���
/// </summary>
void Enemy::collision(Player& player) {
	//�v���C���[�Ƃ̋�����ENEMY_COLLISION_DISTANCE�ȉ��̂Ƃ�
	if (abs(relativeDistance.dx) <= ENEMY_COLLISION_DISTANCE
		&& abs(relativeDistance.dy) <= ENEMY_COLLISION_DISTANCE) {
		dead(); //���S����
		player.lostPlayerCoin(attackPower[level]); //(�v���C���[��)�R�C���̑�������
		player.addAttributeAccumulation(attribute, attributeValue[level]);
	}
}


/// <summary>
/// �������擾
/// </summary>
void Enemy::getAttribute() {
	attribute = getRandom(0, 3);
}

void Enemy::getLevel() {
	level = getRandom(0, 2);
}

/// <summary>
/// ���S���Ԃ��J�E���g
/// </summary>
void Enemy::countDeadTime() {
	if (deadFlag) deadTime++;
	if (deadTime >= 30) {
		deadTime = 0;
		deadFlag = false;
	}
}

/// <summary>
/// ���T�[�W���p�̎��ԃJ�E���g����
/// </summary>
void Enemy::countTime() {
	//lissajousTime��7200�i800��450�̍ŏ����{���j��菬�����Ƃ��A�J�E���g
	lissajousTime = (lissajousTime < 7200) ? ++lissajousTime : 0;
}

/// <summary>
/// ���T�[�W���Ȑ���`��
/// </summary>
void Enemy::lissajous() {
	moveSpeed2.dx = sin(lissajousRandom * lissajousTime / 800) * 10;
	moveSpeed2.dy = cos(lissajousRandom * lissajousTime / 450) * 10;
	pos += moveSpeed2;
}

/// <summary>
/// �����ʒu�̎擾
/// </summary>
void Enemy::initPosition() {
	pos.dx = getPopLocation(ONE_MAP_X, 3, getRandom(AREA_MIN, AREA_MAX)); //x���W
	pos.dy = getPopLocation(ONE_MAP_Y, 3, getRandom(AREA_MIN, AREA_MAX)); //y���W
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
void Enemy::update(Player& player, DataSource& source) {
	relativeDistanceUpdate(player); //�v���C���[�Ƃ̑��΋������擾

	if (player.knife) hitKnife(player); //�i�C�t�����������Ƃ�
	if (player.slash) hitSlash(player); //�n�����������Ƃ�

	countDeadTime();

	if (activity) {
		collision(player); //�v���C���[�Ƃ̏Փˏ���
		if (pattern % 2 == 0)
			tracking.update(player, pos, screenPos); //�ǐՈړ��̍X�V����
		else {
			countTime();
			lissajous();
		}

		draw(source); //�`�揈��
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
	DrawFormatString(200, 230, GetColor(0, 0, 255),
	                 "act�F%d, dead:%d, dTime:%d",
	                 activity, deadFlag, deadTime, false);
	DrawFormatString(200, 260, GetColor(0, 0, 255),
	                 "slash:%d",
	                 player.slash, false);
}

void Enemy::initialize(Player& player) {
	initPosition(); //�����ʒu�̎擾
	getAttribute(); //�������擾
	getLevel(); //���x�����擾
	relativeDistanceUpdate(player); //�v���C���[�Ƃ̑��΋������擾

	pattern = getRandom(0, 3);

	lissajousRandom = getRandom(1, 15);

	if (abs(relativeDistance.dx) <= 500 && abs(relativeDistance.dy) <= 500) {
		activity = true;
	}
}
