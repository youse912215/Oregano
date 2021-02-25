#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"

class GameUI : public DataSource {
private:
	Input& input; //���̓N���X����

	Vec2 pos; //UI�ʒu
	int graphPos; //�摜�ʒu

	void draw(); //�`�揈��
	void actionModeChange(); //�A�N�V�������[�h�̕ύX

public:
	bool changeFlag;

	GameUI(Input& input); //�R���X�g���N�^
	~GameUI(); //�f�X�N�g���N�^

	void update(); //�X�V����
};
