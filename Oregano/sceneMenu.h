#pragma once
#include "inputProcess.h"

class SceneMenu {
private:
	Input& input; //入力クラス

public:
	SceneMenu(Input& input);

	void update();
};
