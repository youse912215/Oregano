#pragma once
#include "dataSource.h"
#include "vec2.h"
#include <vector>

class EffectSpurt : public DataSource {
private:
	Vec2d pos; //���W
	Vec2d movePos;
	Vec2d moveDistance;
	double firstSpeed; //�����x
	double generationTime; //��������
	const double g; //�d�͉����x
	double radius; //���a
	double radian; //���W�A��
	bool isAlive; //�������

	void draw(); //�`�揈��
	void initialize(Vec2d& deadPos); //������
	void occurrenceParticle(Vec2d& deadPos); //�p�[�e�B�N������

public:
	EffectSpurt();
	~EffectSpurt();

	void update(std::vector<EffectSpurt>& spurt, Vec2d& deadPos); //�X�V����
};
