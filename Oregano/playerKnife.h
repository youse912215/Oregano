#pragma once
#include <vector>
#include "inputProcess.h"
#include "vec2.h"
#include "dataSource.h"

class PlayerKnife {
private:
	const double curvatureSpeed; //曲げる速度
	const double maxRange; //ナイフの最大範囲

public:
	Vec2d knifePos; //ナイフ座標
	Vec2d knifeAddPos; //ナイフの加算分の座標

	void initialize(Vec2d& pos, Vec2d& knifeCenter); //ナイフの初期化
	void knifeCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag); //ナイフのクールダウン処理
	void setKnifePosition(Vec2d& pos); //ナイフのポジジョンセット
	void resetKnifePosition(Vec2d& center, bool& knife); //ナイフのポジジョンリセット
	void accelKnife(Input& input); //ナイフの加速
	bool deleteKnife(Vec2d& center); //ナイフの削除条件
	void draw(DataSource& source); //描画処理

	PlayerKnife(); //コンストラクタ
};
