#pragma once
#include "dataSave.h"
#include "inputProcess.h"

class SceneSave {
private:
	DataSave& data; //データセーブクラス
	Input& input; //入力クラス

	const int maxTime; //最大時間
	const int changeTime; //切替時間
	int interval; //間隔時間

public:
	SceneSave(DataSave& data, Input& input);

	void update(); //更新処理
};
