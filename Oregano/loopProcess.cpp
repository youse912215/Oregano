#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "player.h"
#include "enemy.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "mapAutogeneration.h"
#include "eventField.h"
#include "eventBase.h"
#include "dataSave.h"
#include "gameUI.h"
#include "dataText.h"

#include "sceneTitle.h"

#include "effectParticle.h"

void loopProcess() {

	Input input; //入力クラス
	DataSource source; //素材クラス
	Player player(input); //プレイヤークラス

	Enemy enemy;
	vector<Enemy> enemies(20);

	EventBase event; //イベントクラス
	EventField field(input, event, player); //フィールドクラス
	DataText text(input); //テキストクラス
	DataSave save(player, field, text); //セーブデータクラス
	GameUI gameUI(input); //ゲームUIクラス
	SceneTitle title(save);

	EffectParticle particle;
	vector<EffectParticle> particles(100);

	MapAutogeneration mapp;

	while (true) {
		ClearDrawScreen(); //画面クリア

		MapDraw mapDraw_(source.mapChip); //マップクラス
		MapCollision collision(mapDraw_); //コリジョンクラス

		input.update(); //入力処理

		/* タイトルシーン処理 */
		if (EventBase::gameScene == TITLE_SCENE) title.titleProcess();

			/* ゲームシーン処理 */
		else if (EventBase::gameScene == GAME_SCENE) {


			mapDraw_.update(title.returnMapAll()); //マップ更新処理
			collision.update(); //コリジョン更新処理


			//if (!gameUI.changeFlag) //移動処理（アクション変更時は移動不可）
			input.moveProcess(collision);

			field.update(); //フィールド更新処理

			gameUI.update(); //UI更新処理

			for (auto& i : enemies) {
				if (!i.activity && !i.deadFlag) {
					i.initialize(player);
				}
				i.update(player);
				if (i.deadFlag) particle.update(particles, i.screenPos, i.attribute);
			}
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
	/*for (unsigned int i = 0; i != enemies.size(); ++i) {
		delete enemies[i];
	}*/
}
