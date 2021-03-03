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
	dVec2 knifePos; //ナイフ座標
	dVec2 knifeAddPos; //ナイフの加算分の座標

	void initialize(dVec2& pos, dVec2& knifeCenter); //ナイフの初期化
	void knifeCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag); //ナイフのクールダウン処理
	void setKnifePosition(dVec2& pos); //ナイフのポジジョンセット
	void resetKnifePosition(dVec2& center, bool& knife); //ナイフのポジジョンリセット
	void accelKnife(Input& input); //ナイフの加速
	bool deleteKnife(dVec2& center); //ナイフの削除条件
	void draw(DataSource& source); //描画処理

	PlayerKnife(); //コンストラクタ
};
