#pragma once
#include "dataSave.h"
#include "mapLoad.h"
#include <vector>

using namespace std;

class SceneRoad {
private:
	DataSave& save; //�f�[�^�Z�[�u�N���X����
	//MapLoad& load; //�}�b�v���[�h�N���X����
public:
	static int gameScene;

	SceneRoad(DataSave& save);
	~SceneRoad();

	void update(); //�^�C�g������
	vector<vector<vector<int>>>& roadingMap(); //�^�C�g����ʂŃ��[�h�����}�b�v�O�����z���Ԃ�
};
