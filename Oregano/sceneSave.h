#pragma once
#include "dataSave.h"
#include "inputProcess.h"

class SceneSave {
private:
	DataSave& data; //データセーブクラス
	Input& input; //入力クラス

public:
	SceneSave(DataSave& data, Input& input);

	void update(); //更新処理
};
