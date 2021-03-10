#pragma once

class DataSource {
private:

protected:
	int actionUI; //�A�N�V����UI�摜�t�@�C���̓ǂݍ���

public:
	int enemyGraph;
	int player; //�v���C���[
	int playerDamage; //�v���C���[�_���[�W
	int mapChip; //�}�b�v�`�b�v
	int knifeGraph; //�i�C�t
	int slashGraph; //�n
	int shieldGraph; //�V�[���h
	int red; //�ԐF�̌�
	int blue; //�F�̌�
	int green; //�ΐF�̌�
	int yellow; //���F�̌�
	int blurGraph1; //�ڂ���1
	int blurGraph2; //�ڂ���2
	int enemyLife; //�G�̃��C�t
	int coinGraph; //�R�C��UI
	int conditionGraph; //���UI
	int passiveGraph; //�p�b�V�uUI
	int menuGraph; //���j���[UI
	int actionGraph; //�A�N�V����UI
	int filterGraph1; //�A�N�V�����ȊO�̃t�B���^�[UI
	int filterGraph2; //�A�N�V�����̃t�B���^�[UI
	int shieldGauge; //�V�[���h�Q�[�W
	int eventGraph; //�C�x���gUI
	int title; //�^�C�g�����
	int menu; //���j���[���
	int gameover; //�Q�[���I�[�o�[���
	int clear; //�N���A���
	int event1; //�C�x���g���1
	int event2; //�C�x���g���2
	int event3; //�C�x���g���3
	int titleStart; //�^�C�g���{�^������
	int deviceChange1; //�f�o�C�X�ؑ֕���1
	int deviceChange2; //�f�o�C�X�ؑ֕���2
	int gameOverEnd; //�Q�[���I�[�o�[�{�^������

	DataSource();
	~DataSource();
};
