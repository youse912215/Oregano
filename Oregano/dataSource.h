#pragma once

class DataSource {
private:

protected:
	int actionUI; //�A�N�V����UI�摜�t�@�C���̓ǂݍ���

public:
	int enemyGraph;
	int player; //�v���C���[�摜�̓ǂݍ���
	int mapChip; //�}�b�v�`�b�v�摜�t�@�C���̓ǂݍ���
	int knifeGraph;
	int slashGraph;
	int shieldGraph;
	int red;
	int blue;
	int green;
	int yellow;
	int blurGraph1;
	int blurGraph2;
	int enemyLife;
	int coinGraph;
	int conditionGraph;
	int passiveGraph;
	int menuGraph;
	int modeGraph;
	int actionGraph;
	int filterGraph1;
	int filterGraph2;
	int shieldGauge;

	DataSource();
	~DataSource();
};
