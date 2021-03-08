#pragma once
#include <vector>
#include "inputProcess.h"
#include "vec2.h"
#include "dataSource.h"

class PlayerKnife {
private:
	Vec2d center; //中心
	double radian; //角度
	double sign; //符号
	const double curvatureSpeed; //曲げる速度
	const double maxRange; //ナイフの最大範囲
	bool reverseFlag; //反転フラグ

	void changeDirection(Vec2d& pos); //方向変更

public:
	Vec2d knifePos; //ナイフ座標
	Vec2d knifeAddPos; //ナイフの加算分の座標

	void initialize(Vec2d& pos, Vec2d& knifeCenter); //ナイフの初期化
	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag); //ナイフのクールダウン処理
	void setKnifePosition(Vec2d& pos); //ナイフのポジジョンセット
	void resetKnifePosition(Vec2d& playerCenter, vector<bool>& actionFlag); //ナイフのポジジョンリセット
	void accelKnife(Input& input); //ナイフの加速
	bool deleteKnife(Vec2d& playerCenter); //ナイフの削除条件
	void calculateRadian(Vec2d& pos); //描画用のラジアン計算
	void draw(DataSource& source); //描画処理

	PlayerKnife(); //コンストラクタ
};
