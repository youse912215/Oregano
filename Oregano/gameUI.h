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

	const int margin; //�]���T�C�Y

	Vec2 menuLength; //���j���[��
	Vec2 menuSize; //���j���[�T�C�Y
	Vec2 passiveSize; //�p�b�V�u�T�C�Y
	Vec2 conditionSize; //��Ԉُ�T�C�Y
	Vec2 modeLeftSize; //L���[�h�T�C�Y
	Vec2 modeLength; //���[�h��
	Vec2 modeRightSize; //R���[�h�T�C�Y
	Vec2 actionLength; //�A�N�V������
	Vec2 actionSize; //�A�N�V�����T�C�Y

	void drawBlur(); //�ڂ����̕`��
	void draw(); //�`�揈��

	bool changeFlag; //�ؑփt���O

public:


	GameUI(Input& input, MapDraw& map);
	~GameUI();


	void update(); //�X�V����
};
