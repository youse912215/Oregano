#pragma once
#include "player.h"

class EnemyConclusion {
private:
	Player& player_; //プレイヤークラス
	DataSource source_; //データソースクラス

	const int showTime; //最大の表示時間

public:
	EnemyConclusion(Player& player_);

	void update(); //更新処理
};
