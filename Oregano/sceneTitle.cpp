#include "sceneTitle.h"
#include "constant.h"
#include "mapAutogeneration.h"
#include "DxLib.h"

MapAutogeneration autogeneration;

SceneTitle::SceneTitle(DataSave& save, MapLoad& load) : save(save), load(load) {
}

SceneTitle::~SceneTitle() {
}

void SceneTitle::titleProcess() {
	CALL_ONCE(save.roadSaveData()); //�t�@�C���ǂݍ��ݏ���
	CALL_ONCE(autogeneration.writeRandomMap()); //�}�b�v��������
	load.roadMapData();

	EventBase::gameScene = GAME_SCENE;
}

/// <summary>
/// �^�C�g����ʂŃ��[�h�����}�b�v�O�����z���Ԃ�
/// </summary>
vector<vector<vector<int>>>& SceneTitle::returnMapAll() {
	return load.mapAll;
}
