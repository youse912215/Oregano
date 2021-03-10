#include "effectSpurt.h"
#include "DxLib.h"
#include "random.h"
#include <cmath>

EffectSpurt::EffectSpurt() :
	pos(0.0, 0.0), movePos(0.0, 0.0), moveDistance(0.0, 0.0),
	radiusRange(5, 10), radianRange(60, 120), firstSpeed(5.0),
	generationTime(0.0), g(9.8), radius(5.0), radian(0.0), maxTime(10.0), maxRange(150.0),
	colorMax(255), isAlive(false) {
}

EffectSpurt::~EffectSpurt() {
}

void EffectSpurt::draw() {
	SetDrawBlendMode(DX_BLENDMODE_INVSRC, getRandom(0, colorMax)); //���Z�u�����h

	/* �~�̕`�� */
	DrawCircle(static_cast<int>(pos.dx), static_cast<int>(pos.dy), static_cast<int>(radius),
	           GetColor(getRandom(0, colorMax),
	                    getRandom(0, colorMax),
	                    getRandom(0, colorMax)), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�u�����h�I�t
}

/// <summary>
/// ������
/// </summary>
/// <param name="deadPos"�G�����񂾍��W</param>
void EffectSpurt::initialize(Vec2d& deadPos) {
	pos = deadPos;
	radius = getRandomD(radiusRange.x, radiusRange.y); //���a�������_���Ŏ擾
	radian = getRadian(radianRange.x, radianRange.y); //���W�A���������_���Ŏ擾
	isAlive = true; //������Ԃ�true
}

/// <summary>
/// �p�[�e�B�N������
/// </summary>
/// <param name="deadPos">�G�����񂾍��W</param>
void EffectSpurt::occurrenceParticle(Vec2d& deadPos) {
	generationTime++; //�������Ԃ��J�E���g

	movePos.dx = firstSpeed * cos(radian) * (generationTime / maxTime); //x�����̌v�Z
	movePos.dy = firstSpeed * sin(radian) * (generationTime / maxTime)
		- (g * ((generationTime / maxTime) * (generationTime / maxTime))) / 2.0; //y�����̌v�Z

	pos += movePos; //�ړ��|�W�W���������Z
	moveDistance = pos - deadPos; //�ړ��������v�Z

	/* �ړ�������maxRange�̂Ƃ� */
	if (abs(moveDistance.dy) >= maxRange) {
		generationTime = 0.0; //�������Ԃ����Z�b�g
		isAlive = false; //������Ԃ�false
	}

	draw(); //�`�揈��
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="spurt">�p�[�e�B�N���̔z��</param>
/// <param name="deadPos">�G�����񂾍��W</param>
void EffectSpurt::update(std::vector<EffectSpurt>& spurt, Vec2d& deadPos) {
	for (auto& i : spurt) {
		//�p�[�e�B�N�����������Ă��Ȃ��Ƃ�
		if (!i.isAlive) {
			i.initialize(deadPos); //������
			break; //�����o��
		}
		i.occurrenceParticle(deadPos); //�p�[�e�B�N������
	}
}
