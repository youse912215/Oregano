#pragma once
#include "dataSave.h"
#include "inputProcess.h"

class SceneGameOver {
private:
	DataSave& data;
	Input& input;

public:
	bool endFlag; //終了フラグ

	SceneGameOver(DataSave& data, Input& input);

	void update(); //更新処理
};
