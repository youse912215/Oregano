#pragma once
#include "inputProcess.h"

class SceneEnd {
private:
	Input& input; //���̓N���X

	const int maxTime; //�ő厞��
	const int changeTime; //�ؑ֎���
	int interval; //�Ԋu����

public:
	bool endFlag; //�I���t���O

	SceneEnd(Input& input);

	void update(); //�X�V����
};
