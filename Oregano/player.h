#pragma once
#include "organism.h"
#include <vector>

using namespace std;

//ÉvÉåÉCÉÑÅ[
class Player : public Organism {
private:

	int graph;

	void draw();
	void initProcess();

public:
	Vec2 pos;
	Vec2 center;

	vector<int> status;
	vector<int> possessionItem;
	vector<int> possessionAccessory;
	vector<int> possessionJewel;
	vector<int> possessionMineral;

	Player(int graph);
	~Player();

	void update();
};
