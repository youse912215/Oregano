#pragma once
#include "Human.h"

//�v���C���[
class Player : public Human {
public:
	Player();
	~Player();
	void draw();

private:
	int player_graph;
};
