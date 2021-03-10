#pragma once
#include "dataSave.h"
#include "inputProcess.h"
#include "dataSource.h"

class SceneGameOver {
private:
	DataSave& data; //�Z�[�u�f�[�^�N���X
	Input& input; //���̓N���X
	DataSource source; //�f�[�^�\�[�X�N���X

	Vec2 charSize; //�����T�C�Y
	Vec2 charPos; //�����ʒu
	const int charInterval; //�����Ԋu

public:
	bool endFlag; //�I���t���O

	SceneGameOver(DataSave& data, Input& input);

	void update(); //�X�V����
};
