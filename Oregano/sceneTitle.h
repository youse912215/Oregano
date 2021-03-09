#pragma once
#include "inputProcess.h"

class SceneTitle {
private:
	Input& input; //入力クラス

public:
	SceneTitle(Input& input);

	void update(); //更新処理
};
