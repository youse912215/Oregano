#pragma once
#include "vec2.h"
#include <vector>
#include "dataSource.h"

class PlayerSlash {
private:

public:
	Vec2 slashPos; //刃座標

	void initialize(Vec2& pos);
	void slashCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, bool& slash); //刃のクールダウン処理
	void draw(DataSource& source); //描画処理

	PlayerSlash(); //コンストラクタ
};
