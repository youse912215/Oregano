#pragma once
#include "dataSave.h"
#include "mapLoad.h"
#include <vector>

using namespace std;

class SceneLoad {
private:
	DataSave& save; //�f�[�^�Z�[�u�N���X����
	//MapLoad& load; //�}�b�v���[�h�N���X����
public:
	static int gameScene;

	SceneLoad(DataSave& save);
	~SceneLoad();

	void update(); //�^�C�g������
	vector<vector<vector<int>>>& roadingMap(); //�^�C�g����ʂŃ��[�h�����}�b�v�O�����z���Ԃ�
};