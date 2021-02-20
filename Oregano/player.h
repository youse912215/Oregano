#pragma once
#include "Human.h"
#include <vector>

using namespace std;

//ƒvƒŒƒCƒ„[
class Player : public Human {
private:
	Vec2 pos;
	int graph;

	void draw();
	void initProcess();

public:
	vector<int> status;
	vector<int> possessionItem;

	Player(int graph);
	~Player();

	void update();
};
