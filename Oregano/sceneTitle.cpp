#include "sceneTitle.h"
#include "constant.h"
#include "mapAutogeneration.h"
#include "dataSource.h"

MapAutogeneration autogeneration;
MapLoad load;
DataSource source;

SceneTitle::SceneTitle(DataSave& save) : save(save) {
}

SceneTitle::~SceneTitle() {
}

/// <summary>
/// �X�V����
/// </summary>
void SceneTitle::update() {
	CALL_ONCE(save.roadSaveData()); //�t�@�C���ǂݍ��ݏ���
	CALL_ONCE(autogeneration.writeRandomMap()); //�}�b�v��������
	load.roadMapData(); //�}�b�v�f�[�^�ǂݍ���

	EventBase::gameScene = GAME_SCENE; //�Q�[���V�[����
}

/// <summary>
/// �^�C�g����ʂŃ��[�h�����}�b�v�O�����z���Ԃ�
/// </summary>
vector<vector<vector<int>>>& SceneTitle::roadingMap() {
	return load.mapAll;
}
