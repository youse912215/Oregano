#pragma once
#include "inputProcess.h"

class SceneMenu {
private:
	Input& input; //���̓N���X

	const int maxTime; //�ő厞��
	const int changeTime; //�ؑ֎���
	int interval; //�Ԋu����

public:
	SceneMenu(Input& input);

	void update(); //�X�V����
};
