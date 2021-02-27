#pragma once
#include "dataSave.h"
#include "mapLoad.h"
#include <vector>

using namespace std;

class SceneTitle {
private:
	DataSave& save; //�f�[�^�Z�[�u�N���X����
	//MapLoad& load; //�}�b�v���[�h�N���X����
public:
	SceneTitle(DataSave& save);
	~SceneTitle();

	void titleProcess(); //�^�C�g������
	vector<vector<vector<int>>>& returnMapAll(); //�^�C�g����ʂŃ��[�h�����}�b�v�O�����z���Ԃ�
};
