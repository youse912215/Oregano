#pragma once
#include <vector>

class PlayerState {
private:

public:
	std::vector<bool> stateAbnormal; //óÔŮíi0:ŇĹA1:ázšA2:ŹA3:oj

	std::vector<int> attributeAccumulation; //ŽŤĎvl

	int battleStyle; //íŹX^Ci0:ÔGK, 1:[xq, 2:qÔ, 3:gÔj

	void changeBattleStyle(std::vector<int>& coin, const int& dir); //íŹX^CđŘčÖŚé

	void getStateAbnormal();

	void switchStyleAutomatically(std::vector<int>& coin);

	void calculateValue(const int& attribute, const int& attributeValue);

	void valueReset(bool& elimination, std::vector<bool>& cooldownFlag);

	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag);

	PlayerState();
};
