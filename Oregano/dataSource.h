#pragma once

class DataSource {
private:

	//int actionUI; //�A�N�V����UI�摜�t�@�C���̓ǂݍ���

protected:
	int actionUI; //�A�N�V����UI�摜�t�@�C���̓ǂݍ�

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

	DataSource();
	~DataSource();
};
