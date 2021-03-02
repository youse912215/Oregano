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
	Vec2 knifePos; //ナイフ座標
	Vec2 knifeAddPos; //ナイフの加算分の座標

	void initialize(Vec2& pos, Vec2& knifeCenter); //ナイフの初期化
	void knifeCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag); //ナイフのクールダウン処理
	void setKnifePosition(Vec2& pos); //ナイフのポジジョンセット
	void resetKnifePosition(Vec2& center, bool& knife); //ナイフのポジジョンリセット
	void accelKnife(Input& input); //ナイフの加速
	bool deleteKnife(Vec2& center); //ナイフの削除条件
	void draw(DataSource& source); //描画処理

	PlayerKnife(); //コンストラクタ
};
