#pragma once

class DataSource {
private:

	//int actionUI; //�A�N�V����UI�摜�t�@�C���̓ǂݍ���

protected:
	int actionUI; //�A�N�V����UI�摜�t�@�C���̓ǂݍ�

public:
	int enemy1;
	int player; //�v���C���[�摜�̓ǂݍ���
	int mapChip; //�}�b�v�`�b�v�摜�t�@�C���̓ǂݍ���
	int knifeGraph;
	int slashGraph;
	int shieldGraph;

	DataSource();
	~DataSource();

	int playerGraph();
	int mapChipGraph();
};
