#pragma once
#include "inputProcess.h"
#include "dataSource.h"

class SceneEnd : public DataSource {
private:
	Input& input; //���̓N���X
	Vec2 startSize; //�X�^�[�g�����T�C�Y
	Vec2 startPos; //�X�^�[�g�����ʒu

	const int maxTime; //�ő厞��
	const int changeTime; //�ؑ֎���
	int interval; //�Ԋu����

public:
	bool endFlag; //�I���t���O

	SceneEnd(Input& input);

	void update(); //�X�V����
};
