#pragma once
#include "Human.h"

//�v���C���[
class Player : public Human {
public:

	Player(int x, int y, int graph);
	~Player();
	void draw();

private:
	int graph;
};
