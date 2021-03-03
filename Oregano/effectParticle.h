#pragma once
#include "vec2.h"
#include "dataSource.h"
#include <vector>

class EffectParticle {
private:
	DataSource source;

	dVec2 movePos; //移動量
	dVec2 moveDir; //移動方向
	dVec2 pos; //ポジジョン
	dVec2 moveDistance; //移動距離

	double radius; //半径
	double moveSize; //移動サイズ

	bool isAlive; //生存状態
	double generationTime; //発生時間

	const int graphSize; //画像サイズ
	const int minRand; //ランダム最小値
	const int maxRand; //ランダム最大値
	const double maxRange; //最大範囲
	const double maxTime; //最大時間

	void initialize(dVec2& deadPos); //初期化
	void setPosition(dVec2& deadPos); //ポジジョンをセット
	void occurrenceParticle(dVec2& deadPos); //パーティクル発生

public:
	EffectParticle();
	~EffectParticle();

	void update(std::vector<EffectParticle>& particles, dVec2& deadPos); //更新処理

};
