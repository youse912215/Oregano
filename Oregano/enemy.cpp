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
	screenCenter(0.0, 0.0), relativeDistance(0.0, 0.0), life(0), initLife{1, 2, 3}, possessionCoin{5, 15, 25},
	attackPower{5, 25, 50},
	level(0), damageInterval(2), damageFlag(2), attributeValue{15, 30, 50}, lissajousMaxTime(7200.0),

	lissajousX(800.0), lissajousY(450.0), controlSpeed(10.0), lissajousTime(0), lissajousRandom(0),

	pattern(0), screenPos(0.0, 0.0),

	deadTime(0), attribute(0),

	activity(false), deadFlag(false), intervalFlag(2) {

}

Enemy::~Enemy() {
}

/// <summary>
/// �`�揈��
/// </summary>
void Enemy::draw(DataSource& source) {
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
	deadFlag = true; //���S��Ԃ�true
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
		takeDamage(KNIFE); //�_���[�W���󂯂�
	}
}

/// <summary>
/// �n�q�b�g���̏���
/// </summary>
void Enemy::hitSlash() {
	//
	if (abs(relativeDistance.dx) <= 80.0 && abs(relativeDistance.dy) <= 80.0) {
		takeDamage(SLASH); //�_���[�W���󂯂�
	}
}

/// <summary>
/// �_���[�W���󂯂�
/// </summary>
/// <param name="act">�v���C���[�̃A�N�V����</param>
void Enemy::takeDamage(const int& act) {
	if (damageInterval[act] == 0) {
		damageFlag[act] = true;
		intervalFlag[act] = true;
	}
}

/// <summary>
/// �_���[�W����
/// </summary>
/// <param name="act">�v���C���[�̃A�N�V����</param>
void Enemy::damageProcess(Player& player, const int& act) {
	if (intervalFlag[act])
		damageInterval[act]++;

	if (damageInterval[act] >= 15) {
		damageInterval[act] = 0;
		intervalFlag[act] = false;
	}

	if (damageFlag[act]) {
		life -= player.addDamage(act);
		damageFlag[act] = false;
	}
}

/// <summary>
/// 0���C�t�̏���
/// </summary>
void Enemy::noLife(Player& player) {
	if (life <= 0) {
		life = 0;
		dead(); //���S����
		player.addPlayerCoin(attribute, possessionCoin[level]); //�R�C���ǉ�����
	}
}

/// <summary>
/// �v���C���[�Ƃ̏Փˏ���
/// </summary>
void Enemy::collision(Player& player) {
	//�v���C���[�Ƃ̋�����ENEMY_COLLISION_DISTANCE�ȉ��̂Ƃ�
	if (abs(relativeDistance.dx) <= ENEMY_COLLISION_DISTANCE
		&& abs(relativeDistance.dy) <= ENEMY_COLLISION_DISTANCE) {
		life = 0;
		//dead(); //���S����
		player.lostPlayerCoin(attackPower[level]); //(�v���C���[��)�R�C���̑�������
		player.addAttributeAccumulation(attribute, attributeValue[level]); //�����ϋv�l�����Z
	}
}

/// <summary>
/// �X�e�[�^�X��ݒ�
/// </summary>
void Enemy::setStatus() {
	pattern = getRandom(0, 1); //�G�̃p�^�[���������_���Ő���
	lissajousRandom = getRandom(1, 15); //���T�[�W���Ȑ��̎�ނ������_���Ő���
	attribute = getRandom(0, 3); //�����l
	level = getRandom(0, 2); //���x��
	life = initLife[level]; //���C�t
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
	lissajousTime = (lissajousTime < lissajousMaxTime) ? ++lissajousTime : 0;
}

/// <summary>
/// ���T�[�W���Ȑ���`��
/// </summary>
void Enemy::lissajous() {
	lissajousSpeed.dx = sin(lissajousRandom * lissajousTime / lissajousX) * controlSpeed; //x����
	lissajousSpeed.dy = cos(lissajousRandom * lissajousTime / lissajousY) * controlSpeed; //y����
	pos += lissajousSpeed; //�ړ����x�����Z
}

/// <summary>
/// �����ʒu�̎擾
/// ���݂̃v���C���[�̈ʒu������ӂɂ����ďo��
/// </summary>
void Enemy::initPosition(Player& player) {
	//x���W
	pos.dx = getPopLocation(ONE_MAP_X, //�}�b�v�T�C�Y
	                        player.currentMapPos(MAP_X_), //�S�̃}�b�v���W
	                        getRandom(AREA_MIN, AREA_MAX)); //1�����W
	//y���W
	pos.dy = getPopLocation(ONE_MAP_Y, //�}�b�v�T�C�Y
	                        player.currentMapPos(MAP_Y_), //�S�̃}�b�v���W
	                        getRandom(AREA_MIN, AREA_MAX)); //1�����W
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
	if (player.slash) hitSlash(); //�n�����������Ƃ�

	damageProcess(player, KNIFE); //�i�C�t�_���[�W����
	damageProcess(player, SLASH); //�n�_���[�W����

	noLife(player); //0���C�t����

	countDeadTime(); //���S���Ԃ��J�E���g

	if (activity) {
		collision(player); //�v���C���[�Ƃ̏Փˏ���
		if (pattern % 2 == 0)
			tracking.update(player, pos, screenPos); //�ǐՈړ��̍X�V����
		else {
			countTime(); //���T�[�W���p�̎��ԃJ�E���g����
			lissajous(); //���T�[�W���Ȑ��`��
		}
		draw(source); //�`�揈��
	}

	//�G����ʃT�C�Y��2�{�͈̔͊O�ɂ���Ƃ�
	if (abs(relativeDistance.dx) >= WIN_WIDTH && abs(relativeDistance.dy) >= WIN_HEIGHT) {
		dead();
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
	                 "act�F%d, dead:%d, dTime:%d, LIFE:%d, dm1:%d, dm2:%d",
	                 activity, deadFlag, deadTime, life,
	                 player.addDamage(0), player.addDamage(1), false);
}

void Enemy::initialize(Player& player) {
	initPosition(player); //�����ʒu�̎擾
	setStatus(); //�X�e�[�^�X��ݒ�
	relativeDistanceUpdate(player); //�v���C���[�Ƃ̑��΋������擾

	//�G����ʃT�C�Y��2�{�͈͓̔��ɂ���Ƃ�
	if (abs(relativeDistance.dx) <= WIN_WIDTH && abs(relativeDistance.dy) <= WIN_HEIGHT) {
		activity = true; //������Ԃ�true
	}
}
