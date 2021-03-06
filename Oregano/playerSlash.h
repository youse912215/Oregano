#pragma once
#include "vec2.h"
#include <vector>
#include "dataSource.h"

class PlayerSlash {
private:
	int drawTime; //描画時間
	const int graphNum; //画像数
	const int graphWidth; //画像幅
	const int popTime; //刃出現時間
	const int cooldownMax; //最大クールダウン

public:
	Vec2d slashPos; //刃座標

	void initialize(Vec2d& pos); //初期化
	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag,
	                   std::vector<bool>& actionFlag); //刃のクールダウン処理
	void countTime(); //描画時間カウント
	void draw(DataSource& source); //描画処理

	PlayerSlash(); //コンストラクタ
};
