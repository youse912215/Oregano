#pragma once
#include "inputProcess.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "sceneLoad.h"
#include "player.h"
#include "enemyConclusion.h"
#include "gameUI.h"

class SceneGame {
private:
	Input& input; //入力クラス
	MapDraw& draw; //描画クラス
	MapCollision& collision; //コリジョンクラス
	SceneLoad& load; //ロードクラス
	Player& player; //プレイヤークラス
	EnemyConclusion& enemy; //敵まとめクラス
	GameUI& gameUI; //ゲームUIクラス

	const int timeMax; //最大時間
	const int popTime; //出現時間

	void countTime(); //時間をカウント

public:
	int gameTime; //ゲーム時間
	bool enemyFlag; //敵出現フラグ

	SceneGame(Input& input, MapDraw& draw, MapCollision& collision, SceneLoad& load, Player& player,
	          EnemyConclusion& enemy, GameUI& gameUI);

	static void countInterval(int* countTime, const int& maxTime); //間隔時間をカウント

	void update(); //更新処理
};
