#include "sceneTitle.h"
#include "constant.h"
#include "mapAutogeneration.h"

MapAutogeneration autogeneration;

void titleProcess(DataSave save) {
	CALL_ONCE(save.roadSaveData()); //ファイル読み込み処理
	CALL_ONCE(autogeneration.writeRandomMap()); //マップ自動生成
	EventBase::gameScene = GAME_SCENE;
}
