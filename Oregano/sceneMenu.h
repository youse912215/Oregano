#pragma once
#include "inputProcess.h"

class SceneMenu {
private:
	Input& input; //���̓N���X

public:
	SceneMenu(Input& input);

	void update();
};
