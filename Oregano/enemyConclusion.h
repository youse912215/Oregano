#pragma once
#include "player.h"

class EnemyConclusion {
private:
	Player& player_; //プレイヤークラス
	DataSource source_; //データソースクラス

public:
	EnemyConclusion(Player& player_);

	void update(); //更新処理
};
