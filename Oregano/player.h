#pragma once
#include "Human.h"
#include <vector>

using namespace std;

//�v���C���[
class Player : public Human {
private:
	Vec2 pos;
	int graph;

public:
	vector<int> status;

	Player(int graph);
	~Player();
	void draw();
};
