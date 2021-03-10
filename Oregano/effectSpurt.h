#pragma once
#include "dataSource.h"
#include "vec2.h"
#include <vector>

class EffectSpurt : public DataSource {
private:
	Vec2d pos; //���W
	Vec2d movePos; //�ړ����W
	Vec2d moveDistance; //�ړ�����
	Vec2 radiusRange; //���a�͈�
	Vec2 radianRange; //���W�A���͈�

	double firstSpeed; //�����x
	double generationTime; //��������
	const double g; //�d�͉����x
	double radius; //���a
	double radian; //���W�A��

	const double maxTime; //�ő厞��
	const double maxRange; //�ő�͈�
	const int colorMax; //�F�̍ő�RGB

	bool isAlive; //�������

	void draw(); //�`�揈��
	void initialize(Vec2d& deadPos); //������
	void occurrenceParticle(Vec2d& deadPos); //�p�[�e�B�N������

public:
	EffectSpurt();
	~EffectSpurt();

	void update(std::vector<EffectSpurt>& spurt, Vec2d& deadPos); //�X�V����
};
