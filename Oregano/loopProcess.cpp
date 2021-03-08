#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "player.h"
#include "playerState.h"
#include "enemyConclusion.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "dataSave.h"
#include "gameUI.h"

#include "sceneRoad.h"
#include "sceneSave.h"
#include "sceneMenu.h"
#include "sceneGameOver.h"
#include "sceneEnd.h"

void loopProcess() {

	Input input; //入力クラス

	MapDraw draw_; //マップクラス
	MapCollision collision(draw_); //コリジョンクラス
	Player player(input, draw_); //プレイヤークラス
	EnemyConclusion enemy(player); //敵まとめクラス

	GameUI gameUI(input, player, draw_); //ゲームUIクラス

	PlayerState state; //プレイヤー状態クラス
	DataSave data(state, gameUI); //セーブデータクラス

	SceneRoad road(data); //ロードシーンクラス
	SceneSave save(data, input); //セーブシーンクラス
	SceneMenu menu(input); //メニューシーンクラス
	SceneGameOver gameOver(data, input); //ゲームオーバークラス
	SceneEnd end(input); //エンドシーンクラス

	while (true) {
		ClearDrawScreen(); //画面クリア

		input.update(); //入力処理

		/* タイトルシーン処理 */
		if (SceneRoad::gameScene == TITLE_SCENE) {
			if (input.A) SceneRoad::gameScene = ROAD_SCENE;
		}
		/* ロードシーン処理 */
		road.update(); //更新処理

		/* ゲームシーン処理 */
		if (SceneRoad::gameScene == GAME_SCENE) {
			draw_.update(road.roadingMap()); //マップ更新処理

			collision.update(); //コリジョン更新処理

			input.menuProcess(); //メニュー処理
			input.movement(collision, draw_); //移動処理

			player.update(); //プレイヤー更新処理

			//enemy.update(); //敵更新処理

			gameUI.update(); //UI更新処理
		}

		/* セーブシーン処理 */
		save.update(); //更新処理

		/* メニューシーン処理 */
		menu.update(); //更新処理

		/* ゲームオーバーシーン処理 */
		gameOver.update(); //更新処理

		/* エンドシーン処理 */
		end.update(); //更新処理

		if (gameOver.endFlag || end.endFlag) break; //終了処理

		windowSettingInLoop(); //ループ内ウィンドウ設定
		if (ProcessMessage() == -1) break; //Windowsシステムからくる情報を処理
	}
}
