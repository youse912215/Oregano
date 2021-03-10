#pragma once
#include "inputProcess.h"
#include "dataSource.h"
#include "vec2.h"

class SceneMenu : public DataSource {
private:
	Input& input; //���̓N���X

	Vec2 devicePos; //�f�o�C�X�����ʒu
	Vec2 deviceSize; //�f�o�C�X�����T�C�Y

	const int maxTime; //�ő厞��
	const int changeTime; //�ؑ֎���
	int interval; //�Ԋu����

public:
	SceneMenu(Input& input);

	void update(); //�X�V����
};
