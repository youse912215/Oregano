#pragma once
#include "inputProcess.h"

class SceneTitle {
private:
	Input& input; //���̓N���X

public:
	SceneTitle(Input& input);

	void update(); //�X�V����
};
