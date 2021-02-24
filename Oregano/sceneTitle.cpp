#include "sceneTitle.h"
#include "constant.h"

void titleProcess(DataSave save) {
	CALL_ONCE(save.roadSaveData()); //ファイル読み込み処理（一度のみ）
}
