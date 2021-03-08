#pragma once
#include "dataSave.h"
#include "inputProcess.h"

class SceneGameOver {
private:
	DataSave& data;
	Input& input;

public:
	bool endFlag;

	SceneGameOver(DataSave& data, Input& input);

	void update();
};
