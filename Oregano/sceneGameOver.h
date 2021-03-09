#pragma once
#include "dataSave.h"
#include "inputProcess.h"

class SceneGameOver {
private:
	DataSave& data;
	Input& input;

public:
	bool endFlag; //�I���t���O

	SceneGameOver(DataSave& data, Input& input);

	void update(); //�X�V����
};
