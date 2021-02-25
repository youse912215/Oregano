#include "sceneTitle.h"
#include "constant.h"
#include "mapAutogeneration.h"

MapAutogeneration autogeneration;

void titleProcess(DataSave save) {
	CALL_ONCE(save.roadSaveData()); //�t�@�C���ǂݍ��ݏ���
	CALL_ONCE(autogeneration.writeRandomMap()); //�}�b�v��������
	EventBase::gameScene = GAME_SCENE;
}
