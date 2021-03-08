#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "player.h"
#include "playerState.h"
#include "enemyConclusion.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "eventField.h"
#include "dataSave.h"
#include "gameUI.h"
#include "dataText.h"
#include "sceneTitle.h"

void loopProcess() {

	Input input; //入力クラス

	MapDraw draw_; //マップクラス
	MapCollision collision(draw_); //コリジョンクラス
	Player player(input, draw_); //プレイヤークラス
	EnemyConclusion enemy(player); //敵まとめクラス

	GameUI gameUI(input, player, draw_); //ゲームUIクラス

	PlayerState state;
	DataSave save(state, gameUI); //セーブデータクラス
	SceneTitle title(save); //タイトルクラス

	while (true) {
		ClearDrawScreen(); //画面クリア

		input.update(); //入力処理

		/* タイトルシーン処理 */
		if (SceneTitle::gameScene == TITLE_SCENE) {
			if (input.X) SceneTitle::gameScene = ROAD_SCENE;
		}

		/* ロードシーン処理 */
		if (SceneTitle::gameScene == ROAD_SCENE) {
			title.update();
		}

			/* ゲームシーン処理 */
		else if (SceneTitle::gameScene == GAME_SCENE) {
			draw_.update(title.roadingMap()); //マップ更新処理

			collision.update(); //コリジョン更新処理

			input.movement(collision, draw_); //移動処理

			player.update(); //プレイヤー更新処理

			//enemy.update(); //敵更新処理

			gameUI.update(); //UI更新処理
		}
			/* メニューシーン処理 */
		else if (SceneTitle::gameScene == MENU_SCENE) {
		}

			/* ゲームオーバーシーン処理 */
		else if (SceneTitle::gameScene == GAME_OVER_SCENE) {
		}

			/* エンドシーン処理 */
		else if (SceneTitle::gameScene == END_SCENE) {
			save.writeSaveData(); //ファイル書き込み処理（一度のみ）
			break; //終了処理（ループから抜ける）
		}

		windowSettingInLoop(); //ループ内ウィンドウ設定
		if (ProcessMessage() == -1) break; //Windowsシステムからくる情報を処理
	}
}
