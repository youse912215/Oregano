#include "gameUI.h"
#include "DxLib.h"
#include "constant.h"

GameUI::GameUI(Input& input, MapDraw& map) : input(input), map(map), menuSize(256, 64), margin(16) {
	pos.x = WIN_WIDTH - BLOCK_SIZE * 2;
	pos.y = WIN_HEIGHT - BLOCK_SIZE * 2;
	graphPos = 0;
	changeFlag = false;
}

GameUI::~GameUI() {
}

/// <summary>
/// ぼかしの描画
/// </summary>
void GameUI::drawblur() {
	//マップ座標（3, 2）より右上以外は通常ぼかし
	if (!(map.currentMap.x >= 3 && map.currentMap.y <= 2))
		DrawGraph(0, 0, source.blurGraph1, true);
		//さらに視界を狭めるぼかし
	else
		DrawGraph(0, 0, source.blurGraph2, true);
}

/// <summary>
/// 描画処理
/// </summary>
void GameUI::draw() {
	drawblur(); //ぼかし

	DrawGraph(margin, margin, source.coinGraph, true); //コイン
	DrawRectGraph(WIN_WIDTH - menuSize.x - margin, margin,
	              0, 0, menuSize.x, menuSize.y,
	              menuGraph, true, false, false); //メニュー
	DrawGraph(margin, WIN_HEIGHT - 128 - margin, passiveGraph, true); //パッシブ
	DrawGraph(WIN_WIDTH - 256 - margin, WIN_HEIGHT - 128 - margin,
	          conditionGraph, true); //状態異常
	DrawRectGraph(BLOCK_SIZE * 7 - margin, WIN_HEIGHT - 128 - margin,
	              0, 0, 64, 128, modeGraph, true, false, false);
	DrawRectGraph(BLOCK_SIZE * 16 + 32 - margin, WIN_HEIGHT - 128 - margin,
	              64, 0, 64, 128, modeGraph, true, false, false);

}

void GameUI::update() {
	draw();
}
