#include "sceneRoad.h"
#include "constant.h"
#include "mapAutogeneration.h"
#include "dataSource.h"
#include "dataText.h"

MapAutogeneration autogeneration;
MapLoad load;
DataSource source;
DataText text;

int SceneRoad::gameScene = TITLE_SCENE;

SceneRoad::SceneRoad(DataSave& save) : save(save) {
}

SceneRoad::~SceneRoad() {
}

/// <summary>
/// �X�V����
/// </summary>
void SceneRoad::update() {
	if (gameScene == ROAD_SCENE) {
		save.roadMapData(); //�}�b�v�f�[�^�̓ǂݍ���
		save.roadSaveData(); //�Z�[�u�f�[�^�ǂݍ���
		autogeneration.writeRandomMap(); //�}�b�v��������
		load.roadMapData(); //�}�b�v�f�[�^�ǂݍ���
		text.roadFont(); //�t�H���g�̃��[�h

		gameScene = GAME_SCENE; //�Q�[���V�[����
	}
}

/// <summary>
/// �^�C�g����ʂŃ��[�h�����}�b�v�O�����z���Ԃ�
/// </summary>
vector<vector<vector<int>>>& SceneRoad::roadingMap() {
	return load.mapAll;
}
