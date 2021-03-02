#pragma once
#include <vector>
#include "vec2.h"
#include "dataSource.h"

class PlayerShield {
private:

public:
	Vec2 shieldPos; //シールド座標
	int shieldValue; //シールド量

	void initialize(Vec2& pos);
	void shieldCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& shield); //シールドのクールダウン処理
	void draw(DataSource& source);

	PlayerShield();
};
