#pragma once
#include "Human.h"

//�v���C���[
class Player : public Human {
private:
	Vec2 pos;
	int graph;

public:

	Player(int graph);
	~Player();
	void draw();
};
