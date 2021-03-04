#pragma once
#include "mapDraw.h"
#include <vector>

class PlayerState {
private:
	int poisonTime; //�ғŎ���
	int roughTime; //�ʉ�����
	const int attributeMax; //�ő�ϋv�l
	const int timeMax; //�ő厞��
	const int cooldownMax; //�ő�N�[���_�E��
	const int poisonDamage; //�ғłɂ��_���[�W(�����R�C����)
	const int roughDamage; //�ʉ��ɂ��_���[�W(�����R�C����)
	const int eliminateCoin; //�����K�v�R�C��

	void getStateAbnormal(); //��Ԉُ���擾
	void getFloorState(MapDraw& draw_); //����ł̏�Ԃ��擾
	void countStateTime(); //�ғŎ��Ԃ��J�E���g
	void continuousDamage(const int& time, const int& value); //�p���_���[�W��t�^

public:
	vector<bool> stateAbnormal; //��Ԉُ�i0:�ғŁA1:�z���A2:�����A3:�o���j
	vector<int> attributeAccumulation; //�����ϋv�l
	vector<int> coin; //�R�C���iHP�A�U���̖����j

	/*�i0:�ԖG�K(�Ζғ�), 1:�[�x�q(���z��), 2:���q��(�΍���), 3:���g��(�Ώo��)�j*/
	int battleStyle; //�퓬�X�^�C��(0~3)

	void changeBattleStyle(const int& dir); //�퓬�X�^�C����؂�ւ���

	void switchStyleAutomatically(); //���݂̐퓬�X�^�C����ύX
	void calculateValue(const int& attribute, const int& attributeValue); //�����~�ϒl�̌v�Z
	void valueReset(bool& elimination, vector<bool>& cooldownFlag); //�����ϋv�l���̃��Z�b�g
	void countCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag); //��Ԃ̃N�[���_�E������
	void stateAbnormalUpdate(MapDraw& draw_); //��Ԉُ�X�V����

	PlayerState();
};
