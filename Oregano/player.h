#pragma once
#include "Human.h"
#include <vector>

using namespace std;

//ÉvÉåÉCÉÑÅ[
class Player : public Human {
private:
	Vec2 pos;
	int graph;

	void draw();
	void initProcess();

public:
	vector<int> status;
	vector<int> possessionItem;
	vector<int> possessionAccessory;
	vector<int> possessionJewel;
	vector<int> possessionMineral;

	Player(int graph);
	~Player();

	void update();
};
