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
	screenCenter(0.0, 0.0), relativeDistance(0.0, 0.0), lifeHeight(8), intervalMax(15),
	initLife{1, 2, 3, 4}, possessionCoin{1, 2, 3, 4}, attackPower{1, 2, 4, 8},
	attributeValue{1, 2, 3, 5},
	life(0), pattern(0), level(0), damageInterval(2), damageFlag(2),

	lissajousMaxTime(7200.0), lissajousX(800.0), lissajousY(450.0), controlSpeed(10.0), lissajousTime(0),

	lissajousRandom(0), screenPos(0.0, 0.0),

	deadTime(0), attribute(0),

	activity(false), deadFlag(false), intervalFlag(2) {

}

Enemy::~Enemy() {
}

/// <summary>
/// �`�揈��
/// </summary>
void Enemy::draw(DataSource& source) {
	/*�����iattribute�j�ɂ���āA�摜��ύX����*/
	DrawRectGraph(static_cast<int>(screenPos.dx),
	              static_cast<int>(screenPos.dy),
	              attribute * static_cast<int>(HALF_BLOCK_SIZE_D), 0,
	              static_cast<int>(HALF_BLOCK_SIZE_D), static_cast<int>(HALF_BLOCK_SIZE_D),
	              source.enemyGraph, true, false); //�G
	/* life�ɂ���āA�摜��ύX���� */
	DrawRectGraph(static_cast<int>(screenPos.dx),
	              static_cast<int>(screenPos.dy) - 10,
	              0, life * lifeHeight - lifeHeight,
	              static_cast<int>(HALF_BLOCK_SIZE_D), lifeHeight,
	              source.enemyLife, true, false); //life
}

/// <summary>
/// ���S����
/// </summary>
void Enemy::dead() {
	activity = false; //������Ԃ�false
	deadFlag = true; //���S��Ԃ�true
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
	/* �Ԋu�t���O��true�̂Ƃ� */
	if (intervalFlag[act])
		damageInterval[act]++; //�_���[�W�Ԋu���Ԃ��J�E���g

	/* �_���[�W�Ԋu���Ԃ�intervalMax�ُ�Ȃ� */
	if (damageInterval[act] >= intervalMax) {
		damageInterval[act] = 0; //�_���[�W�Ԋu���Ԃ�0
		intervalFlag[act] = false; //�Ԋu�t���O��false
	}

	/* �_���[�W�t���O��true�̂Ƃ� */
	if (damageFlag[act]) {
		life -= player.addDamage(act); //�_���[�W
		damageFlag[act] = false; //�_���[�W�t���O��false
	}
}

/// <summary>
/// 0���C�t�̏���
/// </summary>
void Enemy::noLife(Player& player) {
	if (life <= 0) {
		life = 0; //���C�t��0�ɂ���
		player.addPlayerCoin(attribute, possessionCoin[level]); //�R�C���ǉ�����
		dead(); //���S����
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
		player.addAttributeAccumulation(attribute, attributeValue[level]); //�����ϋv�l�����Z
	}
}

/// <summary>
/// �X�e�[�^�X��ݒ�
/// </summary>
void Enemy::setStatus() {
	pattern = getRandom(0, 4); //�G�̃p�^�[���������_���Ő���
	lissajousRandom = getRandom(1, 15); //���T�[�W���Ȑ��̎�ނ������_���Ő���
	attribute = getRandom(0, 3); //�����l
	level = getRandom(0, 3); //���x��
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
	                        player.currentMapPos(POSITION_X), //�S�̃}�b�v���W
	                        getRandom(AREA_MIN, AREA_MAX)); //1�����W
	//y���W
	pos.dy = getPopLocation(ONE_MAP_Y, //�}�b�v�T�C�Y
	                        player.currentMapPos(POSITION_Y), //�S�̃}�b�v���W
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

	if (player.actionFlag[KNIFE]) hitKnife(player); //�i�C�t�����������Ƃ�
	if (player.actionFlag[SLASH]) hitSlash(); //�n�����������Ƃ�

	damageProcess(player, KNIFE); //�i�C�t�_���[�W����
	damageProcess(player, SLASH); //�n�_���[�W����

	countDeadTime(); //���S���Ԃ��J�E���g

	/* ������Ԃ̂Ƃ� */
	if (activity) {
		collision(player); //�v���C���[�Ƃ̏Փˏ���

		//�p�^�[����0�ȊO�Ȃ�
		if (pattern != 0) {
			countTime(); //���T�[�W���p�̎��ԃJ�E���g����
			lissajous(); //���T�[�W���Ȑ��`��
		}
		else {
			tracking.update(player, pos, screenPos); //�ǐՈړ��̍X�V����
		}

		draw(source); //�`�揈��

		noLife(player); //0���C�t����	
	}

	//�G����ʃT�C�Y��2�{�͈̔͊O�ɂ���Ƃ�
	if (abs(relativeDistance.dx) >= WIN_WIDTH && abs(relativeDistance.dy) >= WIN_HEIGHT) {
		screenPos = -500.0; //��ʊO�Ƀ|�W�V�������Z�b�g
		dead(); //���S����
	}

	/*DrawFormatString(200, 185, GetColor(0, 0, 255),
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
	                 player.addDamage(0), player.addDamage(1), false);*/
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
