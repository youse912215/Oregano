#include "sceneLoad.h"
#include "constant.h"
#include "mapAutogeneration.h"
#include "dataSource.h"
#include "dataText.h"

MapAutogeneration autogeneration;
MapLoad load;
DataSource source;
DataText text;

int SceneLoad::gameScene = TITLE_SCENE; //�^�C�g���V�[��

SceneLoad::SceneLoad(DataSave& save) : save(save) {
}

SceneLoad::~SceneLoad() {
}

/// <summary>
/// �X�V����
/// </summary>
void SceneLoad::update() {
	if (gameScene == ROAD_SCENE) {
		save.loadMapData(); //�}�b�v�f�[�^�̓ǂݍ���
		save.initLoadSaveData(); //�Z�[�u�f�[�^�ǂݍ���
		autogeneration.writeRandomMap(); //�}�b�v��������
		load.loadMapData(); //�}�b�v�f�[�^�ǂݍ���
		autogeneration.resetFile(); //CSV�t�@�C���̃��Z�b�g
		text.loadFont(); //�t�H���g�̃��[�h

		gameScene = GAME_SCENE; //�Q�[���V�[����
	}
}

/// <summary>
/// �^�C�g����ʂŃ��[�h�����}�b�v�O�����z���Ԃ�
/// </summary>
vector<vector<vector<int>>>& SceneLoad::roadingMap() {
	return load.mapAll;
}
