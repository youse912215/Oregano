#pragma once
#include "inputProcess.h"

class SceneEnd {
private:
	Input& input; //���̓N���X

public:
	bool endFlag; //�I���t���O

	SceneEnd(Input& input);

	void update(); //�X�V����
};
