#pragma once
#include "Human.h"

//ƒvƒŒƒCƒ„[
class Player : public Human {
private:
	Vec2 pos;
	int graph;

public:

	Player(int graph);
	~Player();
	void draw();
};
