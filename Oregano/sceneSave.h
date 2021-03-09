#pragma once
#include "dataSave.h"
#include "inputProcess.h"

class SceneSave {
private:
	DataSave& data; //�f�[�^�Z�[�u�N���X
	Input& input; //���̓N���X

	const int maxTime; //�ő厞��
	const int changeTime; //�ؑ֎���
	int interval; //�Ԋu����

public:
	SceneSave(DataSave& data, Input& input);

	void update(); //�X�V����
};
