#pragma once
#include "Human.h"

//ƒvƒŒƒCƒ„[
class Player : public Human {
public:

	Player(int x, int y, int graph);
	~Player();
	void draw();

private:
	int graph;
};
