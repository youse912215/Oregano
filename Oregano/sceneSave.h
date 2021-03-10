#pragma once
#include "dataSave.h"
#include "inputProcess.h"
#include "gameUI.h"
#include "dataSource.h"

class SceneSave : public DataSource {
private:
	DataSave& data; //�f�[�^�Z�[�u�N���X
	Input& input; //���̓N���X
	GameUI& UI; //�Q�[��UI�N���X

	const int maxTime; //�ő厞��
	const int changeTime; //�ؑ֎���
	int interval; //�Ԋu����

public:
	SceneSave(DataSave& data, Input& input, GameUI& UI);

	void update(); //�X�V����
};
