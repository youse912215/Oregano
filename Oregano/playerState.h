#pragma once
#include <vector>

class PlayerState {
private:

public:
	std::vector<bool> stateAbnormal; //状態異常（0:猛毒、1:痙攣、2:混乱、3:出血）

	std::vector<int> attributeAccumulation; //属性耐久値

	int battleStyle; //戦闘スタイル（0:花萌葱, 1:深支子, 2:燕子花, 3:中紅花）

	void changeBattleStyle(std::vector<int>& coin, const int& dir); //戦闘スタイルを切り替える

	void getStateAbnormal();

	void switchStyleAutomatically(std::vector<int>& coin);

	void calculateValue(const int& attribute, const int& attributeValue);

	void valueReset(bool& elimination, std::vector<bool>& cooldownFlag);

	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag);

	PlayerState();
};
