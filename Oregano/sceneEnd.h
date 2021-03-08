#pragma once
#include "inputProcess.h"

class SceneEnd {
private:
	Input& input; //入力クラス

public:
	bool endFlag; //終了フラグ

	SceneEnd(Input& input);

	void update(); //更新処理
};
