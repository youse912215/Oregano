#pragma once
#include "dataSave.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "sceneGame.h"

class SceneGameOver {
private:
	DataSave& data; //�Z�[�u�f�[�^�N���X
	Input& input; //���̓N���X
	SceneGame& game; //�Q�[���N���X
	DataSource source; //�f�[�^�\�[�X�N���X

	Vec2 charSize; //�����T�C�Y
	Vec2 charPos; //�����ʒu

	const int charInterval; //�����Ԋu
	const int maxTime; //�ő厞��

	int interval; //�{�^�����v�b�V���\�ɂȂ�܂ł̊Ԋu����

	bool pushFlag; //�v�b�V���t���O

	void countInterval(); //�Ԋu���Ԃ��J�E���g
	void resetValue(); //�l�̃��Z�b�g
	void draw(); //�`�揈��

public:
	bool endFlag; //�I���t���O

	SceneGameOver(DataSave& data, Input& input, SceneGame& game);

	void update(); //�X�V����
};
