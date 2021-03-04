#pragma once
#include <vector>

class PlayerState {
private:

public:
	std::vector<bool> stateAbnormal; //��Ԉُ�i0:�ғŁA1:�z���A2:�����A3:�o���j

	std::vector<int> attributeAccumulation; //�����ϋv�l

	int battleStyle; //�퓬�X�^�C���i0:�ԖG�K, 1:�[�x�q, 2:���q��, 3:���g�ԁj

	void changeBattleStyle(std::vector<int>& coin, const int& dir); //�퓬�X�^�C����؂�ւ���

	void getStateAbnormal();

	void switchStyleAutomatically(std::vector<int>& coin);

	void calculateValue(const int& attribute, const int& attributeValue);

	void valueReset(bool& elimination, std::vector<bool>& cooldownFlag);

	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag);

	PlayerState();
};
