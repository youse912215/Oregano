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
	Input& input;
	MapDraw& draw;
	MapCollision& collision;
	SceneLoad& load;
	Player& player;
	EnemyConclusion& enemy;
	GameUI& gameUI;

public:
	SceneGame(Input& input, MapDraw& draw, MapCollision& collision, SceneLoad& load, Player& player,
	          EnemyConclusion& enemy, GameUI& gameUI);

	static void countInterval(int* countTime, const int& maxTime); //間隔時間をカウント

	void update(); //更新処理
};
