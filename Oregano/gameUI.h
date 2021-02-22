#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"

class GameUI : public DataSource {
private:
	Input& input;

	Vec2 pos;
	int graphPos;

	void draw();
	void actionModeChange();

public:
	bool changeFlag;

	GameUI(Input& input);
	~GameUI();

	void update();
};
