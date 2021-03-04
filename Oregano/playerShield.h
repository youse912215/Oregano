#pragma once
#include <vector>
#include "vec2.h"
#include "dataSource.h"

class PlayerShield {
private:

public:
	Vec2d shieldPos; //シールド座標
	int value; //シールド量

	void initialize(Vec2d& pos); //初期化
	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& shield); //シールドのクールダウン処理
	void draw(DataSource& source); //描画処理
	void zeroOut(); //0以下は0にする処理

	PlayerShield();
};
