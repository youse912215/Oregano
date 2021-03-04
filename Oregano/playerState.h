#pragma once
#include "mapDraw.h"
#include <vector>

class PlayerState {
private:

public:
	std::vector<bool> stateAbnormal; //óÔŮíi0:ŇĹA1:ázšA2:ŹA3:oj
	std::vector<int> attributeAccumulation; //ŽŤĎvl

	int battleStyle; //íŹX^Ci0:ÔGK, 1:[xq, 2:qÔ, 3:gÔj

	void changeBattleStyle(std::vector<int>& coin, const int& dir); //íŹX^CđŘčÖŚé
	void getStateAbnormal(); //óÔŮíđćž
	void getPoisonState(MapDraw& draw_); //°ăĹŇĹóÔđćž
	void switchStyleAutomatically(std::vector<int>& coin); //ťÝĚíŹX^CđĎX
	void calculateValue(const int& attribute, const int& attributeValue); //ŽŤ~ĎlĚvZ
	void valueReset(bool& elimination, std::vector<bool>& cooldownFlag); //ŽŤĎvlĚZbg
	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag); //óÔĚN[_E

	PlayerState();
};
