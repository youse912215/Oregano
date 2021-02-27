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

	void destroying();

	void collision();
	void getMoveSpeed();

	double screenPosX();
	double screenPosY();
	double relativeDistanceX();
	double relativeDistanceY();

	bool onScreenX();
	bool onScreenY();
	void initPosition();

	double getPopLocation(const int& dir, const int& x1, const int& x2);

public:
	bool activity;
	bool alive;

	Enemy(int graph, Player& player);
	~Enemy();

	void update();
};
