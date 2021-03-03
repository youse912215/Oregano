#pragma once
#include "player.h"

class EnemyConclusion {
private:
	Player& player_; //プレイヤークラス
	DataSource source_; //データソースクラス

public:
	void update(); //更新処理

	EnemyConclusion(Player& player_);
};
