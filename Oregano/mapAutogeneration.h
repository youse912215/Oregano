#pragma once
#include "mapBase.h"

class MapAutoGeneration : public MapBase {
private:
	int index; //�C���f�b�N�X

	int autoGenerationMap(const int& random, const int& randomMapNum); //�}�b�v�̎�������

	void assigningRandomNum(const int& randomMapNum); //�����_���}�b�v�̐����������_���Ɋ��蓖��
	void writeFile(const int& x, const int& y, vector<vector<int>>& map); //csv�t�@�C���̏�������

public:
	MapAutoGeneration();
	~MapAutoGeneration();

	vector<vector<int>> roadMap; //�ǂݍ��񂾃}�b�v���i�[
	vector<vector<vector<int>>> copyMap; //�R�s�[�����S�}�b�v���i�[

	void saveInitMap(const int& x, const int& y); //�ŏ��̃}�b�v��ۑ�
	void resetFile();
	void writeRandomMap(); //�����_���}�b�v�̃t�@�C����������	
};
