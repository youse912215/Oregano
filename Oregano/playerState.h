#pragma once
#include <vector>

class PlayerState {
private:

public:
	std::vector<bool> stateAbnormal; //状態異常（0:猛毒、1:痙攣、2:混乱、3:出血）
	std::vector<int> attributeAccumulation; //属性耐久値

	int battleStyle; //戦闘スタイル（0:花萌葱, 1:深支子, 2:燕子花, 3:中紅花）

	void changeBattleStyle(std::vector<int>& coin, const int& dir); //戦闘スタイルを切り替える
	void getStateAbnormal(); //状態異常を取得
	void switchStyleAutomatically(std::vector<int>& coin); //現在の戦闘スタイルを変更
	void calculateValue(const int& attribute, const int& attributeValue); //属性蓄積値の計算
	void valueReset(bool& elimination, std::vector<bool>& cooldownFlag); //属性耐久値等のリセット
	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag); //状態のクールダウン処理

	PlayerState();
};
