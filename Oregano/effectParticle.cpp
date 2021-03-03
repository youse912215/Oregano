#include "effectParticle.h"
#include "random.h"
#include "constant.h"
#include "DxLib.h"
#include <cmath>

EffectParticle::EffectParticle() :
	movePos(10.0, 10.0), moveDir(1.0, 1.0),
	pos(0.0, 0.0), moveDistance(0.0, 0.0), radius(0.0),

	moveSize(1.5), isAlive(false), generationTime(0.0),
	graphSize(8), minRand(0), maxRand(360), maxRange(50.0), maxTime(180.0),
	blendColor{green, yellow, blue, red} {
}

EffectParticle::~EffectParticle() {
}

/// <summary>
/// �|�W�V�������Z�b�g
/// </summary>
/// <param name="deadPos"></param>
void EffectParticle::setPosition(Vec2d& deadPos) {
	movePos = generationTime * moveDir; //�ړ��ʂ��v�Z
	pos += movePos; //�ړ�
	moveDistance = pos - deadPos; //�����|�W�W��������̋������v�Z
	radius = (maxTime - generationTime) * moveSize / 10.0; //���a���v�Z

	/* �����ꏊ����maxRange�ȏ�̂Ƃ� */
	if (abs(moveDistance.dx) >= maxRange || abs(moveDistance.dy) >= maxRange) {
		generationTime = 0.0; //�������Ԃ����Z�b�g
		pos = deadPos; //�|�W�V���������Z�b�g
		isAlive = false; //������Ԃ�false
	}
}

/// <summary>
/// �p�[�e�B�N������
/// </summary>
/// <param name="deadPos">�G�����񂾍��W</param>
void EffectParticle::occurrenceParticle(Vec2d& deadPos, const int& attribute) {
	generationTime++;

	setPosition(deadPos); //�|�W�V�������Z�b�g

	SetDrawBlendMode(DX_BLENDMODE_ADD, 150); //���Z�u�����h

	/* �f�ނ̕`�� */
	DrawRotaGraph2(static_cast<int>(pos.dx) - static_cast<int>(radius),
	               static_cast<int>(pos.dy) - static_cast<int>(radius),
	               8, 8, radius / 5.0, getAngle(minRand, maxRand),
	               //�G��attribute�ɂ���ĐF���ω�
	               blendColor[attribute], true, false);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�m�[�u�����h

	DrawFormatString(400, 400, GetColor(255, 255, 255),
	                 "dx:%.1lf, dy:%.1lf, Time:%.1lf, L:%d", pos.dx, pos.dy,
	                 radius, isAlive, false);
}

/// <summary>
/// ������
/// </summary>
/// <param name="deadPos">�G�����񂾍��W</param>
void EffectParticle::initialize(Vec2d& deadPos) {
	pos = deadPos; //�|�W�W�����Z�b�g

	/* �����_���ŕ�����؂�ւ��� */
	moveDir.dx = static_cast<double>(changeSign(minRand, maxRand)) * getRandomD(minRand, maxRand) / maxTime;
	moveDir.dy = static_cast<double>(changeSign(minRand, maxRand)) * getRandomD(minRand, maxRand) / maxTime;

	isAlive = true; //�p�[�e�B�N���̐�����Ԃ�true
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="particles">�p�[�e�B�N���̔z��</param>
/// <param name="deadPos">�G�����񂾍��W</param>
void EffectParticle::update(std::vector<EffectParticle>& particles, Vec2d& deadPos, const int& attribute) {
	for (auto& i : particles) {
		//�p�[�e�B�N�����������Ă��Ȃ��Ƃ�
		if (!i.isAlive) {
			i.initialize(deadPos); //������
			//i.changeColor(attribute);
			break; //�����o��
		}
		i.occurrenceParticle(deadPos, attribute); //�p�[�e�B�N������
	}
}
