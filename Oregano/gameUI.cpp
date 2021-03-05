#include "gameUI.h"
#include "DxLib.h"
#include "constant.h"

GameUI::GameUI(Input& input, MapDraw& map) : input(input), map(map) {
	pos.x = WIN_WIDTH - BLOCK_SIZE * 2;
	pos.y = WIN_HEIGHT - BLOCK_SIZE * 2;
	graphPos = 0;
	changeFlag = false;
}

GameUI::~GameUI() {
}

/// <summary>
/// ‚Ú‚©‚µ‚Ì•`‰æ
/// </summary>
void GameUI::drawblur() {
	if (!(map.currentMap.x >= 3 && map.currentMap.y <= 2))
		DrawGraph(0, 0, source.BlurGraph1, true);
	else
		DrawGraph(0, 0, source.BlurGraph2, true);
}

/// <summary>
/// •`‰æˆ—
/// </summary>
void GameUI::draw() {
	drawblur(); //‚Ú‚©‚µ‚Ì•`‰æ
}

void GameUI::update() {
	draw();
}
