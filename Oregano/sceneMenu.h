#pragma once
#include "inputProcess.h"

class SceneMenu {
private:
	Input& input; //入力クラス

	const int maxTime; //最大時間
	const int changeTime; //切替時間
	int interval; //間隔時間

public:
	SceneMenu(Input& input);

	void update(); //更新処理
};
