#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "player.h"
#include "playerState.h"
#include "enemyConclusion.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "dataSave.h"
#include "dataSource.h"
#include "gameUI.h"

#include "sceneTitle.h"
#include "sceneLoad.h"
#include "sceneGame.h"
#include "sceneSave.h"
#include "sceneMenu.h"
#include "sceneGameOver.h"
#include "sceneEnd.h"

void loopProcess() {

	Input input; //入力クラス

	DataSource source; //データソースクラス

	MapDraw draw_; //マップクラス
	MapCollision collision(draw_); //コリジョンクラス
	Player player(input, draw_, source); //プレイヤークラス
	EnemyConclusion enemy(player, source); //敵まとめクラス

	GameUI gameUI(input, player, draw_, source); //ゲームUIクラス

	PlayerState state; //プレイヤー状態クラス
	DataSave data(state, gameUI); //セーブデータクラス

	SceneTitle title(input); //タイトルシーンクラス
	SceneLoad load(data); //ロードシーンクラス
	SceneGame game(input, draw_, collision, load, player, enemy, gameUI); //ゲームシーンクラス
	SceneSave save(data, input, gameUI); //セーブシーンクラス
	SceneMenu menu(input); //メニューシーンクラス
	SceneGameOver gameOver(data, input); //ゲームオーバークラス
	SceneEnd end(input); //エンドシーンクラス

	source.playBgm(); //初期BGM

	while (true) {
		ClearDrawScreen(); //画面クリア

		input.update(); //入力処理

		title.update(); //タイトルシーン更新処理

		load.update(); //ロードシーン更新処理

		game.update(); //ゲームシーン更新処理

		save.update(); //セーブシーン更新処理

		menu.update(); //メニューシーン更新処理

		gameOver.update(); //ゲームオーバーシーン更新処理

		end.update(); //エンドシーン更新処理

		//終了フラグがtrueのとき
		if (gameOver.endFlag || end.endFlag) break; //終了処理

		windowSettingInLoop(); //ループ内ウィンドウ設定
		if (ProcessMessage() == -1) break; //Windowsシステムからくる情報を処理
	}
}
