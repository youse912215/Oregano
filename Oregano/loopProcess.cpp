#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "player.h"
#include "enemyConclusion.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "eventField.h"
#include "eventBase.h"
#include "dataSave.h"
#include "gameUI.h"
#include "dataText.h"

#include "sceneTitle.h"


void loopProcess() {

	Input input; //入力クラス
	DataSource source; //素材クラス
	Player player(input); //プレイヤークラス
	EnemyConclusion enemy(player); //敵まとめクラス
	GameUI gameUI(input); //ゲームUIクラス

	EventBase event; //イベントクラス
	EventField field(input, event, player); //フィールドクラス
	DataText text(input); //テキストクラス
	DataSave save(player, field, text); //セーブデータクラス
	SceneTitle title(save); //タイトルクラス


	while (true) {
		ClearDrawScreen(); //画面クリア

		MapDraw mapDraw_(source.mapChip); //マップクラス
		MapCollision collision(mapDraw_); //コリジョンクラス

		input.update(); //入力処理

		/* タイトルシーン処理 */
		if (EventBase::gameScene == TITLE_SCENE) title.update();

			/* ゲームシーン処理 */
		else if (EventBase::gameScene == GAME_SCENE) {
			mapDraw_.update(title.roadingMap()); //マップ更新処理

			collision.update(); //コリジョン更新処理

			//if (!gameUI.changeFlag) //移動処理（アクション変更時は移動不可）
			input.movement(collision, mapDraw_);

			field.update(); //フィールド更新処理

			gameUI.update(); //UI更新処理2

			//enemy.update(); //敵更新処理
		}
			/* メニューシーン処理 */
		else if (EventBase::gameScene == MENU_ITEM_SCENE) {
			text.update(); //テキスト更新処理
		}
			/* エンドシーン処理 */
		else if (EventBase::gameScene == END_SCENE) {
			CALL_ONCE(save.writeSaveData()); //ファイル書き込み処理（一度のみ）
			break; //終了処理（ループから抜ける）
		}

		windowSettingInLoop(); //ループ内ウィンドウ設定
		if (ProcessMessage() == -1) break; //Windowsシステムからくる情報を処理
	}
}
