#pragma once
#include "Human.h"
#include <vector>

using namespace std;

//ƒvƒŒƒCƒ„[
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
