#pragma once
#include "organism.h"
#include "player.h"

class Enemy : public Organism {
private:
	Player& player;

	Vec2 pos;
	Vec2 center;
	Vec2 distance;
	Vec2 distanceSquared;
	Vec2 distanceNormalized;
	Vec2 moveSpeed;

	bool activity;

	int graph;

	void draw();
	void move();
	void collision();
	void getMoveSpeed();

	int screenPosX();
	int screenPosY();
	int relativeDistanceX();
	int relativeDistanceY();

public:
	Enemy(int graph, Player& player);
	~Enemy();

	void update();
};
