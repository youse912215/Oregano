#pragma once
#include "player.h"
#include <vector>

using namespace std;

class Enemy {
private:
	Player& player;

	Vec2 pos;
	Vec2 center;
	Vec2 distance;
	Vec2 distanceSquared;
	Vec2 distanceNormalized;
	Vec2 moveSpeed;


	int graph;

	void draw();
	void move();

	void dead();

	void hitKnife();
	void hitSlash();

	void collision();
	void getMoveSpeed();

	double screenPosX();
	double screenPosY();
	double relativeDistanceX();
	double relativeDistanceY();

	bool onScreenX();
	bool onScreenY();
	void initPosition();

	double getPopLocation(const int& mapDir, const int& coordinate1, const int& coordinate2);

public:
	bool activity;
	bool alive;

	Enemy(int graph, Player& player);
	~Enemy();

	void update();
};
