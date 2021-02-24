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
#include "gameUI.h"
#include "dataText.h"

void loopProcess() {

	Input input; //入力クラス
	DataSource source; //素材クラス
	Player player(source.playerGraph()); //プレイヤークラス
	EventBase event; //イベントクラス
	EventField field(input, event, player); //フィールドクラス
	DataSave save(player, field); //セーブデータクラス
	GameUI gameUI(input);
	DataText text(save);

	while (true) {
		ClearDrawScreen(); //画面クリア

		MapDraw map(source.mapChipGraph()); //マップクラス
		MapCollision collision(map); //コリジョンクラス

		input.update(); //入力更新処理

		if (EventBase::gameScene == TITLE_SCENE)
			CALL_ONCE(save.roadSaveData()); //ファイル読み込み処理（一度のみ）

		if (EventBase::gameScene == GAME_SCENE) {
			map.update(); //マップ更新処理
			collision.update(); //コリジョン更新処理


			if (!gameUI.changeFlag) //移動処理（アクション変更時は移動不可）
				input.moveProcess(collision.leftCollisionFlag(), collision.rightCollisionFlag(),
				                  collision.upCollisionFlag(), collision.downCollisionFlag());

			event.update();

			field.update(); //フィールド更新処理

			save.update(); //データ更新処理

			player.update(); //プレイヤー更新処理

			gameUI.update();

			text.update();
		}

		if (EventBase::gameScene == END_SCENE) {
			CALL_ONCE(save.writeSaveData()); //ファイル書き込み処理（一度のみ）
			break; //終了処理
		}

		windowSettingInLoop(); //ループ内ウィンドウ設定
		if (ProcessMessage() == -1) break; //Windowsシステムからくる情報を処理
	}
}
