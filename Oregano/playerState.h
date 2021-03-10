#pragma once
#include "mapDraw.h"
#include <vector>

class PlayerState {
private:
	DataSource source__;

	int poisonTime; //�ғŎ���
	int roughTime; //�ʉ�����
	const int attributeMax; //�ő�ϋv�l
	const int timeMax; //�ő厞��
	const int cooldownMax; //�ő�N�[���_�E��
	const int poisonDamage; //�ғłɂ��_���[�W(�����R�C����)
	const int roughDamage; //�ʉ��ɂ��_���[�W(�����R�C����)
	const int recoveryCoin; //�����K�v�R�C��

	void getCondition(); //��Ԉُ���擾
	void getFloorState(MapDraw& draw_); //����ł̏�Ԃ��擾
	void countStateTime(); //�ғŎ��Ԃ��J�E���g
	void continuousDamage(const int& time, const int& value); //�p���_���[�W��t�^
	void resetCoin(); //�R�C����0�Ƀ��Z�b�g

public:
	static vector<bool> condition; //��Ԉُ�i0:�ғŁA1:�z���A2:�����A3:�o���j
	static vector<int> attributeAccumulation; //�����ϋv�l
	static vector<int> coin; //�R�C���iHP�A�U���̖����j

	/*�i0:�ԖG�K(�Ζғ�), 1:�[�x�q(���z��), 2:���q��(�΍���), 3:���g��(�Ώo��)�j*/
	static int battleStyle; //�퓬�X�^�C��(0~3)

	bool poisonDamageFlag; //�ғŃ_���[�W�t���O
	bool roughDamageFlag; //�ʉ��_���[�W�t���O

	bool anyCondition(); //�����ꂩ�̏�Ԉُ��Ԃ�
	int addConditionDamage(); //��Ԉُ�ɂ��ǉ��_���[�W

	void resetDamageFlag(); //�_���[�W�t���O�����Z�b�g
	void changeBattleStyle(const int& dir); //�퓬�X�^�C����؂�ւ���
	void switchStyleAutomatically(); //���݂̐퓬�X�^�C����ύX
	void calculateValue(const int& attribute, const int& attributeValue); //�����~�ϒl�̌v�Z
	void valueReset(vector<bool>& actionFlag, vector<bool>& cooldownFlag); //�����ϋv�l���̃��Z�b�g
	void countCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag); //��Ԃ̃N�[���_�E������
	void conditionUpdate(MapDraw& draw_); //��Ԉُ�X�V����

	PlayerState();
};
