#include "sceneGame.h"

SceneGame::SceneGame(Input& input, MapDraw& draw, MapCollision& collision, SceneLoad& load, Player& player,
                     EnemyConclusion& enemy, GameUI& gameUI) :
	input(input), draw(draw), collision(collision), load(load), player(player), enemy(enemy), gameUI(gameUI) {
}

/// <summary>
/// 間隔時間をカウント
/// </summary>
/// <param name="countTime">カウントする時間</param>
/// <param name="maxTime">最大時間</param>
void SceneGame::countInterval(int* countTime, const int& maxTime) {
	if (countTime == nullptr) { return; } //nullチェック

	*countTime = (*countTime <= maxTime) ? ++(*countTime) : 0; //時間をカウントし、最大時間が過ぎると0に戻す
}

void SceneGame::update() {
	if (SceneLoad::gameScene == GAME_SCENE) {
		draw.update(load.roadingMap()); //マップ更新処理

		collision.update(); //コリジョン更新処理

		input.menuProcess(); //メニュー処理
		input.movement(collision, draw); //移動処理

		player.update(); //プレイヤー更新処理

		//enemy.update(); //敵更新処理

		gameUI.update(); //UI更新処理
	}
}
