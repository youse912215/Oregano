#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "mapDraw.h"
//#include "player.h"

class GameUI : public DataSource {
private:
	Input& input; //���̓N���X
	MapDraw& map; //�}�b�v�`��N���X
	DataSource source; //�\�[�X�N���X

	Vec2 pos; //UI�ʒu
	Vec2 menuSize; //���j���[�T�C�Y
	
	int graphPos; //�摜�ʒu
	const int margin; //�]���T�C�Y

	void drawblur(); //�ڂ����̕`��
	void draw(); //�`�揈��

public:
	bool changeFlag;

	GameUI(Input& input, MapDraw& map);
	~GameUI();


	void update(); //�X�V����
};
