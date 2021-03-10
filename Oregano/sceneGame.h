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

public:
	SceneGame(Input& input, MapDraw& draw, MapCollision& collision, SceneLoad& load, Player& player,
	          EnemyConclusion& enemy, GameUI& gameUI);

	static void countInterval(int* countTime, const int& maxTime); //間隔時間をカウント

	void update(); //更新処理
};
