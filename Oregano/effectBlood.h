#pragma once
#include "dataSource.h"
#include "vec2.h"
#include <vector>

class EffectBlood : public DataSource {
private:
	Vec2d movePos; //移動量
	Vec2d moveDir; //移動方向
	Vec2d pos; //座標
	Vec2d moveDistance; //移動距離

	double radius; //半径
	double moveSize; //移動サイズ

	bool isAlive; //生存状態
	double generationTime; //発生時間

	const int graphSize; //画像サイズ
	const int minRand; //ランダム最小値
	const int maxRand; //ランダム最大値
	const double maxRange; //最大範囲
	const double maxTime; //最大時間

	std::vector<int> color; //パーティクル用の色

	void initialize(Vec2d& deadPos); //初期化
	void setPosition(Vec2d& deadPos); //ポジジョンをセット
	void occurrenceParticle(Vec2d& deadPos, const int& attribute); //パーティクル発生
	void draw(const int& attribute); //描画処理

public:
	EffectBlood();
	~EffectBlood();

	void update(std::vector<EffectBlood>& particles, Vec2d& deadPos, const int& attribute); //更新処理

};
