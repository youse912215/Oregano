#pragma once
#include "dataSave.h"
#include "inputProcess.h"
#include "gameUI.h"
#include "dataSource.h"

class SceneSave {
private:
	DataSave& data; //データセーブクラス
	Input& input; //入力クラス
	GameUI& UI; //ゲームUIクラス
	DataSource source; //データソースクラス

	const int maxTime; //最大時間
	const int changeTime; //切替時間
	int interval; //間隔時間

public:
	SceneSave(DataSave& data, Input& input, GameUI& UI);

	void update(); //更新処理
};
