#pragma once
#include <vector>
#include "vec2.h"
#include "dataSource.h"

class PlayerShield {
private:
	Vec2 gaugePos;

	const int shieldQuantity; //通常のシールド量
	const int addQuantity; //追加のシールド量
	const int cooldownMax; //最大クールダウン

	int addShield(const int& battleStyle); //シールドを追加で付与

public:
	Vec2d shieldPos; //シールド座標
	int value; //現在のシールド量

	void initialize(Vec2d& pos); //初期化
	void countCooldown(std::vector<int>& cooldown, std::vector<bool>& cooldownFlag, std::vector<bool>& actionFlag);
	//シールドのクールダウン処理
	void draw(DataSource& source); //描画処理
	void zeroOut(); //0以下は0にする処理
	void giveShield(const int& battleStyle); //シールドを付与

	PlayerShield();
};
