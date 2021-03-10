#pragma once
#include "inputProcess.h"
#include "dataSource.h"
#include "vec2.h"

class SceneTitle {
private:
	Input& input; //���̓N���X
	DataSource source; //�f�[�^�\�[�X�N���X

	Vec2 deviceSize; //�f�o�C�X�����T�C�Y
	Vec2 startSize; //�X�^�[�g�����T�C�Y
	Vec2 startPos; //�X�^�[�g�����ʒu

public:
	SceneTitle(Input& input);

	void update(); //�X�V����
};
