#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "player.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "eventField.h"
#include "eventBase.h"
#include "dataSave.h"

void loopProcess() {

	Input input; //入力クラス
	DataSource source; //素材クラス
	Player player(source.playerGraph()); //プレイヤークラス
	EventBase event; //イベントクラス
	DataSave data(player); //セーブデータクラス
	EventField field(input, event, player); //フィールドクラス

	while (true) {
		ClearDrawScreen(); //画面クリア

		MapDraw map(source.mapChipGraph()); //マップクラス
		MapCollision collision(map); //コリジョンクラス

		CALL_ONCE(data.roadSaveData());

		map.update(); //マップ更新処理

		input.update(); //入力更新処理
		input.moveProcess(collision.leftCollisionFlag(), collision.rightCollisionFlag(),
		                  collision.upCollisionFlag(), collision.downCollisionFlag());

		field.update(); //フィールド更新処理

		data.update(); //データ更新処理

		if (EventBase::gameScene == END_SCENE) {
			CALL_ONCE(data.writeSaveData()); //ファイル書き込み処理（一度のみ）
			break; //終了処理
		}

		player.draw(); //プレイヤー描画処理

		windowSettingInLoop(); //ループ内ウィンドウ設定
		if (ProcessMessage() == -1) break; //Windowsシステムからくる情報を処理
	}
}
