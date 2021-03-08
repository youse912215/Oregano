#pragma once
#include "vec2.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "mapDraw.h"
#include "player.h"
#include <vector>

class GameUI : public DataSource {
private:
	Input& input; //���̓N���X
	Player& player;
	MapDraw& map; //�}�b�v�`��N���X
	DataSource source; //�\�[�X�N���X

	const int margin; //�]���T�C�Y
	const int eventSize; //�C�x���g��
	const int eventLength; //1�C�x���g������̏��T�C�Y��

	Vec2 menuLength; //���j���[��
	Vec2 menuSize; //���j���[�T�C�Y
	Vec2 passiveSize; //�p�b�V�u�T�C�Y
	Vec2 conditionSize; //��Ԉُ�T�C�Y
	Vec2 modeLeftSize; //L���[�h�T�C�Y
	Vec2 modeLength; //���[�h��
	Vec2 modeRightSize; //R���[�h�T�C�Y
	Vec2 actionLength; //�A�N�V������
	Vec2 actionSize; //�A�N�V�����T�C�Y
	Vec2 speechBalloonPos; //�����o���ʒu

	bool positionMatchDecision(const int& i); //�v���C���[�ƃC�x���g�ʒu�̈�v����

	void drawBlur(); //�ڂ����̕`��
	void drawFilter(); //UI�̃t�B���^�̕`��
	void drawSpeechBalloon(); //�C�x���g�p�����o���̕`��
	void draw(); //�`�揈��

public:
	vector<int> mapEventPos; //�C�x���g���W

	int eventNum; //�Z�[�u�t���O

	GameUI(Input& input, Player& player, MapDraw& map);
	~GameUI();


	void update(); //�X�V����
};
