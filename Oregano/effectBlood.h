#pragma once
#include "dataSource.h"
#include "vec2.h"
#include <vector>

class EffectBlood : public DataSource {
private:
	Vec2d movePos; //�ړ���
	Vec2d moveDir; //�ړ�����
	Vec2d pos; //���W
	Vec2d moveDistance; //�ړ�����

	double radius; //���a
	double moveSize; //�ړ��T�C�Y

	bool isAlive; //�������
	double generationTime; //��������

	const int graphSize; //�摜�T�C�Y
	const int minRand; //�����_���ŏ��l
	const int maxRand; //�����_���ő�l
	const double maxRange; //�ő�͈�
	const double maxTime; //�ő厞��

	std::vector<int> color; //�p�[�e�B�N���p�̐F

	void initialize(Vec2d& deadPos); //������
	void setPosition(Vec2d& deadPos); //�|�W�W�������Z�b�g
	void occurrenceParticle(Vec2d& deadPos, const int& attribute); //�p�[�e�B�N������
	void draw(const int& attribute); //�`�揈��

public:
	EffectBlood();
	~EffectBlood();

	void update(std::vector<EffectBlood>& particles, Vec2d& deadPos, const int& attribute); //�X�V����

};