#pragma once
#include "inputProcess.h"

class SceneEnd {
private:
	Input& input; //入力クラス

	const int maxTime; //最大時間
	const int changeTime; //切替時間
	int interval; //間隔時間

public:
	bool endFlag; //終了フラグ

	SceneEnd(Input& input);

	void update(); //更新処理
};
