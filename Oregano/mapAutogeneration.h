#pragma once
#include "mapBase.h"

class MapAutogeneration : public MapBase {
private:
	vector<vector<int>> roadMap; //�ǂݍ��񂾃}�b�v���i�[


	int autogenerationMap(const int& random, const int& randomMapNum); //�}�b�v�̎�������

	void AssigningRandomNum(const int& randomMapNum); //�����_���}�b�v�̐����������_���Ɋ��蓖��
	void fileWrite(const int& x, const int& y); //csv�t�@�C���̏�������

public:
	MapAutogeneration();
	~MapAutogeneration();

	void writeRandomMap(); //�����_���}�b�v�̃t�@�C����������	
};
