#pragma once

class DataSource {
private:
	int player; //�v���C���[�摜�̓ǂݍ���
	int mapChip; //�}�b�v�`�b�v�摜�t�@�C���̓ǂݍ���

public:
	DataSource();
	~DataSource();

	int playerGraph();
	int mapChipGraph();
};
