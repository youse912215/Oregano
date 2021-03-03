#pragma once
#include "vec2.h"
#include "dataSource.h"
#include <vector>

class EffectParticle {
private:
	DataSource source;

	dVec2 movePos; //�ړ���
	dVec2 moveDir; //�ړ�����
	dVec2 pos; //�|�W�W����
	dVec2 moveDistance; //�ړ�����

	double radius; //���a
	double moveSize; //�ړ��T�C�Y

	bool isAlive; //�������
	double generationTime; //��������

	const int graphSize; //�摜�T�C�Y
	const int minRand; //�����_���ŏ��l
	const int maxRand; //�����_���ő�l
	const double maxRange; //�ő�͈�
	const double maxTime; //�ő厞��

	void initialize(dVec2& deadPos); //������
	void setPosition(dVec2& deadPos); //�|�W�W�������Z�b�g
	void occurrenceParticle(dVec2& deadPos); //�p�[�e�B�N������

public:
	EffectParticle();
	~EffectParticle();

	void update(std::vector<EffectParticle>& particles, dVec2& deadPos); //�X�V����

};
