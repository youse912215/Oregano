#pragma once
#include "Human.h"

//ƒvƒŒƒCƒ„[
class Player : public Human {
public:
	Player();
	~Player();
	void draw();

private:
	int player_graph;
};
