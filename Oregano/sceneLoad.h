#pragma once
#include "dataSave.h"
#include "mapAutogeneration.h"
#include <vector>

using namespace std;

class SceneLoad {
private:
	DataSave& save; //�f�[�^�Z�[�u�N���X����
	MapAutoGeneration& mapAuto;

public:
	static int gameScene; //�Q�[���V�[��

	SceneLoad(DataSave& save, MapAutoGeneration& mapAuto);
	~SceneLoad();

	void update(); //�^�C�g������
	vector<vector<vector<int>>>& roadingMap(); //�^�C�g����ʂŃ��[�h�����}�b�v�O�����z���Ԃ�
};
